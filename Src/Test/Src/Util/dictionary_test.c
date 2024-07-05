#include "Util/dictionary.h"
#include "minunit.h"

dictionary_t dict;

float kp           = 1.0;
double ki          = 2.0;
int kd             = 3;
uint32_t system_id = 4;
uint16_t setpoint  = 5;

MU_TEST(dictionary_test)
{
    init_dictionary(&dict);
    add_key_value_pair(&dict, "kp", &kp, FLOAT_TYPE_RANDOLF);
    add_key_value_pair(&dict, "ki", &ki, DOUBLE_TYPE_RANDOLF);
    add_key_value_pair(&dict, "kd", &kd, INT_TYPE_RANDOLF);
    add_key_value_pair(&dict, "system_id", &system_id, UINT32_TYPE_RANDOLF);
    add_key_value_pair(&dict, "setpoint", &setpoint, UINT16_TYPE_RANDOLF);
    mu_check(get_dictionary_value(&dict, "kp") == 1.0);
    mu_check(get_dictionary_value(&dict, "ki") == 2.0);
    mu_check(get_dictionary_value(&dict, "kd") == 3.0);
    mu_check(get_dictionary_value(&dict, "system_id") == 4.0);
    mu_check(get_dictionary_value(&dict, "setpoint") == 5.0);
    kp        = 10.0;
    ki        = 20.0;
    kd        = 30;
    system_id = 40;
    setpoint  = 50;
    mu_check(get_dictionary_value(&dict, "kp") == 10.0);
    mu_check(get_dictionary_value(&dict, "ki") == 20.0);
    mu_check(get_dictionary_value(&dict, "kd") == 30.0);
    mu_check(get_dictionary_value(&dict, "system_id") == 40.0);
    mu_check(get_dictionary_value(&dict, "setpoint") == 50.0);

    set_dictionary_value(&dict, "kp", 100.0);
    set_dictionary_value(&dict, "ki", 200.0);
    set_dictionary_value(&dict, "kd", 300.0);
    set_dictionary_value(&dict, "system_id", 400.0);
    set_dictionary_value(&dict, "setpoint", 500.0);

    mu_check(kp == 100.0);
    mu_check(ki == 200.0);
    mu_check(kd == 300);
    mu_check(system_id == 400);
    mu_check(setpoint == 500);

    mu_check(get_dictionary_value(&dict, "kp") == 100.0);
    mu_check(get_dictionary_value(&dict, "ki") == 200.0);
    mu_check(get_dictionary_value(&dict, "kd") == 300);
    mu_check(get_dictionary_value(&dict, "system_id") == 400);
    mu_check(get_dictionary_value(&dict, "setpoint") == 500);

    char all_keys[50];
    get_all_keys(&dict, all_keys);
    mu_check(strcmp(all_keys, "kp,ki,kd,system_id,setpoint") == 0);
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
