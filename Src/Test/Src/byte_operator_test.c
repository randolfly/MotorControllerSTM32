#include "byte_operator.h"
#include "minunit.h"
#include <stdio.h>

void test_setup(void)
{
    printf("\ntest initialization\n");
}

void test_teardown(void)
{
    /* Nothing */
}

MU_TEST(float_to_uint8_array_test)
{
    float src_float = 1.0f;
    uint8_t dst[4]  = {0};
    float_to_uint8_array(src_float, dst);
    mu_check(dst[0] == 0x00);
    mu_check(dst[1] == 0x00);
    mu_check(dst[2] == 0x80);
    mu_check(dst[3] == 0x3f);
}

MU_TEST(uint8_array_to_float_test)
{
    float test_float          = 1.0f;
    uint8_t src_byte_array[4] = {0x00, 0x00, 0x80, 0x3f};
    test_float                = uint8_array_to_float(src_byte_array);
    mu_check(test_float == 1.0f);
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_TEST(float_to_uint8_array_test);
    MU_RUN_TEST(uint8_array_to_float_test);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
