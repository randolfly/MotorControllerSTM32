#include "ringbuffer.h"
#include "minunit.h"

ring_buffer_t ring_buffer;

void test_setup(void)
{
    printf("\nRING BUFFER TEST STARTED\n");
    static uint8_t buffer[256];
    ring_buffer_init(&ring_buffer, buffer, sizeof(buffer));
}

void test_teardown(void)
{
    printf("\nRING BUFFER TEST STOPED\n");
}

MU_TEST(insert_element_to_buffer_test)
{
    int i, cnt;
    uint8_t tmp = 0;

    for (i = 0; i < 100; i++) {
        ring_buffer_queue(&ring_buffer, i);
    }
    mu_check(ring_buffer_num_items(&ring_buffer) == 100);

    /* Peek third element */
    cnt = ring_buffer_peek(&ring_buffer, &tmp, 3);
    /* Assert byte returned */
    mu_check(cnt == 1);
    /* Assert contents */
    mu_check(tmp == 3);

    for (i = 0; i < 100; i++) {
        uint8_t data;
        ring_buffer_dequeue(&ring_buffer, &data);
        mu_assert_int_eq(i, data);
    }
}

MU_TEST(insert_array_to_buffer_test)
{
    int i;
    uint8_t data[100];
    for (i = 0; i < 100; i++) {
        data[i] = i;
    }
    ring_buffer_queue_arr(&ring_buffer, data, 100);
    mu_check(!ring_buffer_is_empty(&ring_buffer));
    mu_check(ring_buffer_num_items(&ring_buffer) == 100);

    uint8_t data_out[100];
    ring_buffer_dequeue_arr(&ring_buffer, data_out, 100);
    for (i = 0; i < 100; i++) {
        mu_assert_int_eq(i, data_out[i]);
    }
}

MU_TEST(insert_outrange_array_to_buffer_test)
{
    int i, cnt;
    uint8_t tmp = 0;
    uint8_t data[257];
    for (i = 0; i < 257; i++) {
        data[i] = i;
    }
    ring_buffer_queue_arr(&ring_buffer, data, 257);

    /* Peek third element */
    cnt = ring_buffer_peek(&ring_buffer, &tmp, 256);
    /* Assert byte returned */
    mu_check(cnt == 1);
    /* Assert contents */
    mu_check(tmp == 256);

    /* Peek third element */
    cnt = ring_buffer_peek(&ring_buffer, &tmp, 1);
    /* Assert byte returned */
    mu_check(cnt == 1);
    /* Assert contents */
    mu_check(tmp == 257);
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(insert_element_to_buffer_test);
    MU_RUN_TEST(insert_array_to_buffer_test);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
