#include "Controller/motion_statemachine.h"
#include "minunit.h"
#include <stdio.h>

motor_t motor1;
motion_state_machine_t msm;

void test_setup(void)
{
    printf("INIT motion_statemachine_test\n");
    init_motion_state_machine(&msm);
}

void test_teardown(void)
{
    printf("FINISH motion_statemachine_test\n");
}

MU_TEST(motion_state_machine_test)
{
    mu_check(msm.event.idle_to_exit == 0);
    mu_check(msm.event.idle_to_pos == 0);
    mu_check(msm.event.idle_to_vel == 0);
    mu_check(msm.event.idle_to_torque == 0);
    mu_check(msm.event.init_to_poweron == 0);
    mu_check(msm.event.pos_to_idle == 0);
    mu_check(msm.event.torque_to_idle == 0);
    mu_check(msm.event.vel_to_idle == 0);

    mu_check(msm.state == MOTION_INIT);

    msm.event.init_to_poweron = 1;
    update_motion_state_machine(&msm);
    mu_check(msm.state == MOTION_POWERON);
    mu_check(msm.event.init_to_poweron == 0);

    update_motion_state_machine(&msm);
    mu_check(msm.state == MOTION_IDLE);

    msm.event.idle_to_pos = 1;
    update_motion_state_machine(&msm);
    mu_check(msm.state == MOTION_POSMODE);
    mu_check(msm.event.idle_to_pos == 0);

    msm.event.pos_to_idle = 1;
    update_motion_state_machine(&msm);
    mu_check(msm.state == MOTION_IDLE);
    mu_check(msm.event.pos_to_idle == 0);

    msm.event.idle_to_vel = 1;
    update_motion_state_machine(&msm);
    mu_check(msm.state == MOTION_VELMODE);
    mu_check(msm.event.idle_to_vel == 0);

    msm.event.vel_to_idle = 1;
    update_motion_state_machine(&msm);
    mu_check(msm.state == MOTION_IDLE);
    mu_check(msm.event.vel_to_idle == 0);

    msm.event.idle_to_torque = 1;
    update_motion_state_machine(&msm);
    mu_check(msm.state == MOTION_TORQUEMODE);
    mu_check(msm.event.idle_to_torque == 0);

    msm.event.torque_to_idle = 1;
    update_motion_state_machine(&msm);
    mu_check(msm.state == MOTION_IDLE);
    mu_check(msm.event.torque_to_idle == 0);

    msm.event.idle_to_exit = 1;
    update_motion_state_machine(&msm);
    mu_check(msm.state == MOTION_EXIT);
    mu_check(msm.event.idle_to_exit == 0);

    update_motion_state_machine(&msm);
    mu_check(msm.state == MOTION_EXIT);
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(motion_state_machine_test);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
