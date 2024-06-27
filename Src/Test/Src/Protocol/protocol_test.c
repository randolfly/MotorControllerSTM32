#include "protocol.h"
#include "minunit.h"
#include <stdio.h>

static uint8_t protocol_frame_byte_buffer[PROTOCOL_FRAME_MAX_SIZE] = {0};

void test_setup(void)
{
    printf("\n PROTOCOL TEST STARTED\n");
}

void test_teardown(void)
{
    printf("\n PROTOCOL TEST STOPED\n");
}

void init_test_protocol_frame(protocol_frame_t *frame)
{
    frame->header   = PROTOCOL_FRAME_HEADER;
    frame->motor_id = MOTOR_ID1;
    frame->cmd      = SEND_VEL_PID_CMD;
    frame->data     = NULL;
    frame->len      = PROTOCOL_FRAME_HEADER_SIZE + PROTOCOL_FRAME_CHECKSUM_SIZE + 0;
}

MU_TEST(checksum_calculation_test)
{
    printf("start checksum_calculation_test\n");
    uint8_t tmp_checksum, target_checksum;
    // test checksum calculation
    uint8_t test_data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    tmp_checksum        = calculate_checksum(0, test_data, sizeof(test_data));
    target_checksum     = 0x0f;
    mu_check(tmp_checksum == target_checksum);

    // overflow checksum calculation test
    uint8_t test_data_overflow[] = {0xff, 0xff, 0xff, 0xff, 0xff};
    tmp_checksum                 = calculate_checksum(0, test_data_overflow, sizeof(test_data_overflow));
    target_checksum              = 0xFB;
    mu_check(tmp_checksum == target_checksum);
}

MU_TEST(protocol_frame_serialize_test)
{
    printf("start serialize_deserialize_frame_data_test\n");
    protocol_frame_t protocal_frame = {0};
    protocol_frame_t test_frame     = {0};

    init_test_protocol_frame(&protocal_frame);
    serialize_frame_data(protocol_frame_byte_buffer, &protocal_frame);
    deserialize_frame_data(protocol_frame_byte_buffer, &test_frame);

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
    MU_RUN_TEST(protocol_frame_serialize_test);
    MU_RUN_TEST(checksum_calculation_test);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
