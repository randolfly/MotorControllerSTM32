#include "Util/dictionary.h"
#include "minunit.h"

dictionary_t dict;

float kp        = 1.0;
float ki        = 2.0;
float kd        = 3.0;
float system_id = 4.0;

MU_TEST(dictionary_test)
{
    init_dictionary(&dict);
    add_key_value_pair(&dict, "kp", &kp);
    add_key_value_pair(&dict, "ki", &ki);
    add_key_value_pair(&dict, "kd", &kd);
    add_key_value_pair(&dict, "system_id", &system_id);
    mu_check(*get_value(&dict, "kp") == 1.0);
    mu_check(*get_value(&dict, "ki") == 2.0);
    mu_check(*get_value(&dict, "kd") == 3.0);
    mu_check(*get_value(&dict, "system_id") == 4.0);
    kp        = 10.0;
    ki        = 20.0;
    kd        = 30.0;
    system_id = 40.0;
    mu_check(*get_value(&dict, "kp") == 10.0);
    mu_check(*get_value(&dict, "ki") == 20.0);
    mu_check(*get_value(&dict, "kd") == 30.0);
    mu_check(*get_value(&dict, "system_id") == 40.0);
}

MU_TEST_SUITE(test_suite)
{
    MU_RUN_TEST(dictionary_test);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
