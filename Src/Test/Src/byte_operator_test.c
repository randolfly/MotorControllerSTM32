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

MU_TEST(uint8_array_float_array_convert_test)
{
    float eps = 1e-5;
    // the latter test can be carried with random float array
    float float_array[] = {1.0f, 1e-8f, 0.1f, 0.001f, 1.0f, 0.0f, 22222.29f, 1990129012121.4f, 211212e10f};
    // uint8_t size_float_array                  = sizeof(float_array) / sizeof(float_array[0]);
    float test_array[9]        = {0};
    uint8_t uint8_array[9 * 4] = {0};
    float_array_to_uint8_array(float_array, uint8_array, 9);
    uint8_array_to_float_array(uint8_array, test_array, 9 * 4);

    for (uint16_t i = 0; i < 9; i++) {
        mu_check(abs(float_array[i] - test_array[i]) < eps);
    }
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_TEST(float_to_uint8_array_test);
    MU_RUN_TEST(uint8_array_to_float_test);
    MU_RUN_TEST(uint8_array_float_array_convert_test);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
