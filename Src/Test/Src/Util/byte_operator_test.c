#include "Util/byte_operator.h"
#include "minunit.h"
#include <stdio.h>

void test_setup(void)
{
    printf("\nBYTE OPERATOR TEST STARTED\n");
}

void test_teardown(void)
{
    printf("\nBYTE OPERATOR TEST STOPED\n");
}

MU_TEST(double_to_uint8_array_test)
{
    double src_double                   = 1.0;
    uint8_t dst[DATALOG_DATA_TYPE_SIZE] = {0};
    double_to_uint8_array(src_double, dst);
    mu_check(dst[0] == 0x00);
    mu_check(dst[1] == 0x00);
    mu_check(dst[2] == 0x00);
    mu_check(dst[3] == 0x00);
    mu_check(dst[4] == 0x00);
    mu_check(dst[5] == 0x00);
    mu_check(dst[6] == 0xf0);
    mu_check(dst[7] == 0x3f);
}

MU_TEST(uint8_array_to_double_test)
{
    double test_double                             = 1.0;
    uint8_t src_byte_array[DATALOG_DATA_TYPE_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f};
    test_double                                    = uint8_array_to_double(src_byte_array);
    mu_check(test_double == 1.0);
}

MU_TEST(uint8_array_double_array_convert_test)
{
    double eps = 1e-5;
    // the latter test can be carried with random double array
    double double_array[] = {1.0, 1e-8, 0.1, 0.001, 1.0, 0.0, 22222.29, 1990129012121.4, 211212e10};
    // uint8_t size_double_array                  = sizeof(double_array) / sizeof(double_array[0]);
    double test_array[9]                            = {0};
    uint8_t uint8_array[9 * DATALOG_DATA_TYPE_SIZE] = {0};
    double_array_to_uint8_array(double_array, uint8_array, sizeof(double_array) / sizeof(double_array[0]));
    uint8_array_to_double_array(uint8_array, test_array, sizeof(uint8_array) / sizeof(uint8_array[0]));

    for (uint16_t i = 0; i < sizeof(double_array) / sizeof(double); i++) {
        mu_check(abs(double_array[i] - test_array[i]) < eps);
    }
}

MU_TEST(uint8_array_name_string_convert_test)
{
    char name_string_array[100] = "kp,ki,kd,test,system_id";
    uint8_t uint8_array[100]    = {0};
    name_string_to_uint8_array(name_string_array, uint8_array, strlen(name_string_array));
    char test_name_string_array[100] = {0};
    uint8_array_to_name_string(uint8_array, test_name_string_array, sizeof(uint8_array));

    for (uint8_t i = 0; i < sizeof(name_string_array); i++) {
        mu_check(test_name_string_array[i] == name_string_array[i]);
    }
}

MU_TEST(uint8_array_to_name_string_test)
{
    uint8_t src_byte_array[] = {
        0x6b,
        0x70};
    char name_string_array[100]     = {0};
    char target_name_string_array[] = "kp";
    uint8_array_to_name_string(src_byte_array, name_string_array, sizeof(src_byte_array));
    for (uint8_t i = 0; i < sizeof(src_byte_array); i++) {
        mu_check(target_name_string_array[i] == name_string_array[i]);
    }
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_TEST(double_to_uint8_array_test);
    MU_RUN_TEST(uint8_array_to_double_test);
    MU_RUN_TEST(uint8_array_double_array_convert_test);
    MU_RUN_TEST(uint8_array_to_name_string_test);
    MU_RUN_TEST(uint8_array_name_string_convert_test);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
