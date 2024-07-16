#include "Protocol/protocol_parser.h"
#include "Util/byte_operator.h"
#include "minunit.h"

protocol_frame_parser_t parser;

void byte_array_compare(uint8_t *array1, uint8_t *array2, uint16_t size);
void check_parse_frame_result(protocol_frame_t *protocol_frame);

void test_setup(void)
{
    printf("\n PROTOCOL PARSER TEST STARTED\n");
    init_protocol_parser(&parser);
}

void test_teardown(void)
{
    printf("\n PROTOCOL PARSER TEST STOPED\n");
    deinit_protocol_parser(&parser);
}

void init_test_protocol_frame(protocol_frame_t *frame)
{
    frame->header   = PROTOCOL_FRAME_HEADER;
    frame->motor_id = MOTOR_ID1;
    frame->cmd      = DATALOG_ECHO_SET_LOG_DATA_CMD;
    frame->data     = NULL;
    frame->len      = PROTOCOL_FRAME_HEADER_SIZE + PROTOCOL_FRAME_CHECKSUM_SIZE + 0;
}

void check_parse_frame_result(protocol_frame_t *protocol_frame)
{
    mu_check(parser.frame->header == protocol_frame->header);
    mu_check(parser.frame->motor_id == protocol_frame->motor_id);
    mu_check(parser.frame->len == protocol_frame->len);
    mu_check(parser.frame->cmd == protocol_frame->cmd);
    mu_check(parser.frame->checksum == protocol_frame->checksum);
    uint16_t data_size = protocol_frame->len - PROTOCOL_FRAME_HEADER_SIZE - PROTOCOL_FRAME_CHECKSUM_SIZE;
    if (data_size > 0) {
        byte_array_compare(parser.frame->data, protocol_frame->data, data_size);
    }
}

void byte_array_compare(uint8_t *array1, uint8_t *array2, uint16_t size)
{
    for (uint16_t i = 0; i < size; i++) {
        mu_check(array1[i] == array2[i]);
    }
}

MU_TEST(protocol_frame_parser_init_test)
{
    mu_check(parser.ring_buffer->buffer != NULL);
    mu_check(parser.ring_buffer->buffer_mask == PROTOCOL_RECURSIVE_BUFFER_SIZE - 1);
    mu_check(parser.ring_buffer->tail_index == 0);
    mu_check(parser.ring_buffer->head_index == 0);

    mu_check(parser.frame->header == 0);
    mu_check(parser.frame->motor_id == 0);
    mu_check(parser.frame->len == 0);
    mu_check(parser.frame->cmd == 0);
    mu_check(parser.frame->data != NULL);
}

MU_TEST(protocol_frame_header_check_test)
{
    uint8_t protocol_frame_byte_buffer[PROTOCOL_FRAME_MAX_SIZE] = {0};
    protocol_frame_t protocol_frame                             = {0};
    init_test_protocol_frame(&protocol_frame);
    serialize_frame_data(protocol_frame_byte_buffer, &protocol_frame);
    protocol_data_receive(&parser, protocol_frame_byte_buffer, PROTOCOL_FRAME_HEADER_SIZE);

    int64_t head_id = find_frame_header(parser.ring_buffer, 0, PROTOCOL_FRAME_HEADER_SIZE);
    mu_check(head_id == 0);
}

MU_TEST(protocol_frame_nulldata_receive_test)
{
    uint8_t protocol_frame_byte_buffer[PROTOCOL_FRAME_MAX_SIZE] = {0};
    protocol_frame_t protocol_frame                             = {0};
    init_test_protocol_frame(&protocol_frame);
    serialize_frame_data(protocol_frame_byte_buffer, &protocol_frame);
    protocol_data_receive(&parser, protocol_frame_byte_buffer, protocol_frame.len);
    uint16_t cmd_type = protocol_data_handler(&parser);
    mu_check(cmd_type == protocol_frame.cmd);
    check_parse_frame_result(&protocol_frame);
}

MU_TEST(protocol_frame_doublearray_receive_test)
{
    uint8_t protocol_frame_byte_buffer[PROTOCOL_FRAME_MAX_SIZE] = {0};
    protocol_frame_t protocol_frame                             = {0};
    init_test_protocol_frame(&protocol_frame);

    protocol_frame.cmd                          = DATALOG_GET_AVAILABLE_DATA_CMD;
    protocol_frame.motor_id                     = MOTOR_ID2;
    double data[]                               = {1.0, 2.0, 3.0};
    uint8_t byte_array[PROTOCOL_FRAME_MAX_SIZE] = {0};
    double_array_to_uint8_array(data, byte_array, 3);
    set_frame_data(&protocol_frame, byte_array, 3 * DATALOG_DATA_TYPE_SIZE);

    serialize_frame_data(protocol_frame_byte_buffer, &protocol_frame);
    protocol_data_receive(&parser, protocol_frame_byte_buffer, protocol_frame.len);
    uint16_t cmd_type = protocol_data_handler(&parser);
    mu_check(cmd_type == protocol_frame.cmd);
    check_parse_frame_result(&protocol_frame);

    cmd_type = protocol_data_handler(&parser);
    mu_check(cmd_type == NULL_CMD);
    mu_check(parser.frame->cmd == NULL_CMD);
}

MU_TEST(protocol_frame_namestring_receive_test)
{
    uint8_t protocol_frame_byte_buffer[PROTOCOL_FRAME_MAX_SIZE] = {0};
    protocol_frame_t protocol_frame                             = {0};
    init_test_protocol_frame(&protocol_frame);

    protocol_frame.cmd                          = DATALOG_GET_AVAILABLE_DATA_CMD;
    protocol_frame.motor_id                     = MOTOR_ID2;
    char name_string[]                          = "kp,ki,kd,system_id";
    uint8_t byte_array[PROTOCOL_FRAME_MAX_SIZE] = {0};
    name_string_to_uint8_array(name_string, byte_array, strlen(name_string));
    set_frame_data(&protocol_frame, byte_array, strlen(name_string));

    serialize_frame_data(protocol_frame_byte_buffer, &protocol_frame);
    protocol_data_receive(&parser, protocol_frame_byte_buffer, protocol_frame.len);
    uint16_t cmd_type = protocol_data_handler(&parser);
    mu_check(cmd_type == protocol_frame.cmd);
    check_parse_frame_result(&protocol_frame);

    cmd_type = protocol_data_handler(&parser);
    mu_check(cmd_type == NULL_CMD);
    mu_check(parser.frame->cmd == NULL_CMD);
}

MU_TEST(protocol_multiple_frames_parse_test)
{
    uint8_t protocol_frame_byte_buffer[PROTOCOL_FRAME_MAX_SIZE] = {0};
    protocol_frame_t protocol_frame1                            = {0};
    protocol_frame_t protocol_frame2                            = {0};
    protocol_frame_t protocol_frame3                            = {0};
    protocol_frame_t protocol_frame4                            = {0};
    init_test_protocol_frame(&protocol_frame1);
    init_test_protocol_frame(&protocol_frame2);
    init_test_protocol_frame(&protocol_frame3);
    init_test_protocol_frame(&protocol_frame4);

    protocol_frame1.cmd = DATALOG_GET_AVAILABLE_DATA_CMD;
    protocol_frame2.cmd = DATALOG_RUNNING_CMD;

    protocol_frame3.cmd                         = DATALOG_ECHO_SET_LOG_DATA_CMD;
    protocol_frame3.motor_id                    = MOTOR_ID2;
    char name_string[]                          = "kp,ki,kd,system_id";
    uint8_t byte_array[PROTOCOL_FRAME_MAX_SIZE] = {0};
    name_string_to_uint8_array(name_string, byte_array, strlen(name_string));
    set_frame_data(&protocol_frame3, byte_array, strlen(name_string));

    protocol_frame4.cmd = DATALOG_RUNNING_CMD;

    serialize_frame_data(protocol_frame_byte_buffer, &protocol_frame1);
    protocol_data_receive(&parser, protocol_frame_byte_buffer, protocol_frame1.len);
    serialize_frame_data(protocol_frame_byte_buffer, &protocol_frame2);
    protocol_data_receive(&parser, protocol_frame_byte_buffer, protocol_frame2.len);
    serialize_frame_data(protocol_frame_byte_buffer, &protocol_frame3);
    protocol_data_receive(&parser, protocol_frame_byte_buffer, protocol_frame3.len);
    serialize_frame_data(protocol_frame_byte_buffer, &protocol_frame4);
    protocol_data_receive(&parser, protocol_frame_byte_buffer, protocol_frame4.len);

    uint16_t cmd_type = protocol_data_handler(&parser);
    mu_check(cmd_type == protocol_frame1.cmd);
    check_parse_frame_result(&protocol_frame1);

    cmd_type = protocol_data_handler(&parser);
    mu_check(cmd_type == protocol_frame2.cmd);
    check_parse_frame_result(&protocol_frame2);

    cmd_type = protocol_data_handler(&parser);
    mu_check(cmd_type == protocol_frame3.cmd);
    check_parse_frame_result(&protocol_frame3);

    cmd_type = protocol_data_handler(&parser);
    mu_check(cmd_type == protocol_frame4.cmd);
    check_parse_frame_result(&protocol_frame4);
}

MU_TEST(protocol_50_frames_parse_test)
{
    uint8_t protocol_frame_byte_buffer[PROTOCOL_FRAME_MAX_SIZE] = {0};
    protocol_frame_t protocol_frame                             = {0};
    init_test_protocol_frame(&protocol_frame);
    char name_string[]                          = "kp,ki,kd,system_id";
    uint8_t byte_array[PROTOCOL_FRAME_MAX_SIZE] = {0};
    name_string_to_uint8_array(name_string, byte_array, strlen(name_string));

    for (uint16_t i = 0; i < 20; i++) {
        protocol_frame.cmd = DATALOG_GET_AVAILABLE_DATA_CMD;
        set_frame_data(&protocol_frame, byte_array, strlen(name_string));

        serialize_frame_data(protocol_frame_byte_buffer, &protocol_frame);
        protocol_data_receive(&parser, protocol_frame_byte_buffer, protocol_frame.len);
    }

    for (uint16_t i = 0; i < 20; i++) {
        uint16_t cmd_type = protocol_data_handler(&parser);
        mu_check(cmd_type == protocol_frame.cmd);
        check_parse_frame_result(&protocol_frame);
    }

    uint16_t cmd_type = protocol_data_handler(&parser);
    mu_check(cmd_type == NULL_CMD);
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(protocol_frame_parser_init_test);
    MU_RUN_TEST(protocol_frame_header_check_test);
    MU_RUN_TEST(protocol_frame_nulldata_receive_test);
    MU_RUN_TEST(protocol_frame_doublearray_receive_test);
    MU_RUN_TEST(protocol_frame_namestring_receive_test);
    MU_RUN_TEST(protocol_multiple_frames_parse_test);
    MU_RUN_TEST(protocol_50_frames_parse_test);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
