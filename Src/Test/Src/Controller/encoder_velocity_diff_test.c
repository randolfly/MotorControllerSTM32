#include "Controller/encoder_velocity_diff.h"
#include "minunit.h"
#include <stdio.h>

encoder_velocity_diff_t velocity_diff;

// todo: add file export functionality? compare result
void test_setup(void)
{
    printf("\n ENCODER VELOCITY DIFF TEST STARTED\n");
    init_encoder_velocity_diff(&velocity_diff);
}

void test_teardown(void)
{
    printf("\n PROTOCOL TEST STOPED\n");
    deinit_encoder_velocity_diff(&velocity_diff);
}

MU_TEST(hello)
{
    printf("start checksum_calculation_test\n");

    mu_check(1 == 1);
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(hello);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
