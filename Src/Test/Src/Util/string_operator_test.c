#include "Util/string_operator.h"
#include "minunit.h"

MU_TEST(seperate_string_test)
{
    char name[20] = "kp,ki,kd,system_id";
    char *name_list[4];
    int num = 0;
    seperate_string(name, name_list, &num);
    mu_check(strcmp(name_list[0], "kp") == 0);
    mu_check(strcmp(name_list[1], "ki") == 0);
    mu_check(strcmp(name_list[2], "kd") == 0);
    mu_check(strcmp(name_list[3], "system_id") == 0);
    mu_check(num == 4);
}

MU_TEST_SUITE(test_suite)
{
    MU_RUN_TEST(seperate_string_test);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
