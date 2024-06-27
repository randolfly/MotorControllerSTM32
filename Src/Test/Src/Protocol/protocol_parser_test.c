#include "Protocol/protocol_parser.h"
#include "minunit.h"

protocol_frame_parser_t parser;

void test_setup(void)
{
    printf("\n PROTOCOL PARSER TEST STARTED\n");
    protocol_parser_init(&parser);
}

void test_teardown(void)
{
    printf("\n PROTOCOL PARSER TEST STOPED\n");
    protocol_parser_deinit(&parser);
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
    mu_check(parser.frame->data == NULL);
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(protocol_frame_parser_init_test);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
