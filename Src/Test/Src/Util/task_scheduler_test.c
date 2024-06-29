#include "Util/task_scheduler.h"
#include "minunit.h"

static int hello1_test = 0;
static int hello2_test = 0;

void hello1_func(void);
void hello2_func(void);

void test_setup(void)
{
    printf("\nRING BUFFER TEST STARTED\n");
    task_scheduler_init(10);
}

void test_teardown(void)
{
    printf("\nRING BUFFER TEST STOPED\n");
    task_scheduler_deinit();
}

void hello1_func(void)
{
    hello1_test += 1;
}

void hello2_func(void)
{
    hello2_test += 1;
}

MU_TEST(task_run_test)
{
    hello1_test = 0;
    hello2_test = 0;
    task_scheduler_add_task(hello1_func, 2, 1);
    task_scheduler_add_task(hello2_func, 3, 1);
    uint32_t i = 0;
    for (i = 0; i < 100; i++) {
        task_scheduler_tick();
        task_scheduler_run();
    }
    mu_check(hello1_test == 50); // 100/2=50
    mu_check(hello2_test == 34); // 100/3+1=34
}

MU_TEST(task_start_stop_test)
{
    hello1_test = 0;
    hello2_test = 0;
    int id1     = task_scheduler_add_task(hello1_func, 2, 0);
    int id2     = task_scheduler_add_task(hello2_func, 3, 0);
    uint32_t i  = 0;
    for (i = 0; i < 100; i++) {
        if (i == 60) {
            task_scheduler_enable_task(id1);
        }
        if (i == 75) {
            task_scheduler_disable_task(id1);
            task_scheduler_enable_task(id2);
        }
        task_scheduler_tick();
        task_scheduler_run();
    }
    mu_check(hello1_test == 8); // 15/2+1=8
    mu_check(hello2_test == 9); // (100-75)/3+1=9
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_TEST(task_run_test);
    MU_RUN_TEST(task_start_stop_test);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
