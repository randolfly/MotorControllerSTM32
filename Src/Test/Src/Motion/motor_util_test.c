#include "Motion/motor_util.h"
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

MU_TEST(torque_permillage_to_dac_test)
{
    float torque_cmd1 = -1000.0;
    float torque_cmd2 = 1000.0;
    float torque_cmd3 = 0.0;

    mu_check(torque_permillage_to_dac(torque_cmd1) == 0);
    mu_check(torque_permillage_to_dac(torque_cmd2) == 0xFF);
    mu_check(torque_permillage_to_dac(torque_cmd3) == (0xFF / 2));

    torque_cmd1 = -10000.0;
    torque_cmd2 = 10000.0;
    torque_cmd3 = 1001.0;

    mu_check(torque_permillage_to_dac(torque_cmd1) == 0);
    mu_check(torque_permillage_to_dac(torque_cmd2) == 0xFF);
    mu_check(torque_permillage_to_dac(torque_cmd3) == 0xFF);
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(torque_permillage_to_dac_test);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
