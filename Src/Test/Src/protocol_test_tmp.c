#include "protocol.h"
#include "minunit.h"
#include <stdio.h>

/**
 * @brief write frame data to the protocol parser ring buffer
 * @param  frame: single protocol frame data
 */
static void write_frame_buf(protocol_frame_t *frame);

// test protocal frame data pool
static uint8_t protocal_data_pool[PROTOCOL_RECURSIVE_BUFFER_SIZE] = {0};
static int frame_parse_result                                     = 0;

extern protocol_frame_parser_t parser;
extern uint8_t recursive_buffer[PROTOCOL_RECURSIVE_BUFFER_SIZE];

void test_setup(void)
{
    protocol_init();
    printf("\ntest initialization\n");
}

void test_teardown(void)
{
    /* Nothing */
}

void init_test_protocol_frame(protocol_frame_t *frame)
{
    frame->header   = PROTOCOL_FRAME_HEADER;
    frame->motor_id = MOTOR_ID1;
    frame->cmd      = SEND_VEL_PID_CMD;
    frame->data     = NULL;
    frame->len      = PROTOCOL_FRAME_HEADER_SIZE + PROTOCOL_FRAME_CHECKSUM_SIZE + 0;
}

MU_TEST(serialize_deserialize_frame_data_test)
{
    printf("start serialize_deserialize_frame_data_test\n");
    protocol_frame_t protocal_frame = {0};
    protocol_frame_t test_frame     = {0};

    init_test_protocol_frame(&protocal_frame);
    serialize_frame_data(protocal_data_pool, &protocal_frame);
    deserialize_frame_data_from_dest(protocal_data_pool, &test_frame);

    mu_check(protocal_frame.header == test_frame.header);
    mu_check(protocal_frame.motor_id == test_frame.motor_id);
    mu_check(protocal_frame.cmd == test_frame.cmd);
    mu_check(protocal_frame.len == test_frame.len);
    mu_check(protocal_frame.data == test_frame.data);
    mu_check(protocal_frame.checksum == test_frame.checksum);
}

MU_TEST(protocol_data_receive_test)
{
    uint16_t check_read_offset, check_write_offset;
    printf("start protocol_data_receive_test\n");
    protocol_frame_t protocal_frame = {0};
    init_test_protocol_frame(&protocal_frame);

    check_read_offset  = parser.write_offset;
    check_write_offset = parser.write_offset + protocal_frame.len;
    write_frame_buf(&protocal_frame);

    for (uint16_t i = check_read_offset; i < check_write_offset; i++) {
        mu_check(protocal_data_pool[i] == recursive_buffer[i % PROTOCOL_RECURSIVE_BUFFER_SIZE]);
    }
}

MU_TEST(SEND_VEL_PID_CMD_test)
{
    printf("start protocol_data_receive_test\n");
    protocol_frame_t protocal_frame = {0};
    protocol_frame_t test_frame     = {0};
    init_test_protocol_frame(&protocal_frame);

    write_frame_buf(&protocal_frame);
    frame_parse_result = protocol_data_handler();
    mu_check(frame_parse_result == SEND_VEL_PID_CMD);
    mu_check(parser.found_frame_head == 0);
    mu_check(parser.read_offset == protocal_frame.len);

    deserialize_frame_data(&test_frame);

    mu_check(protocal_frame.header == test_frame.header);
    mu_check(protocal_frame.motor_id == test_frame.motor_id);
    mu_check(protocal_frame.cmd == test_frame.cmd);
    mu_check(protocal_frame.len == test_frame.len);
    mu_check(protocal_frame.data == test_frame.data);
    mu_check(protocal_frame.checksum == test_frame.checksum);
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_TEST(serialize_deserialize_frame_data_test);
    MU_RUN_TEST(protocol_data_receive_test);
    MU_RUN_TEST(SEND_VEL_PID_CMD_test);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}

static void write_frame_buf(protocol_frame_t *frame)
{
    serialize_frame_data(protocal_data_pool, frame);
    protocol_data_receive(protocal_data_pool, frame->len);
}