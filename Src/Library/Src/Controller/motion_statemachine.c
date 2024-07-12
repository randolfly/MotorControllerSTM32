#include "Controller/motion_statemachine.h"
#include "Util/task_scheduler.h"
#include "Controller/model_excitation.h"
#include "spi_bsp.h"

// exten task scheduler handles
// ! note: also can define the actions as function pointer, init them in
// main_app.c and pass them to the state machine. here we just use the extern handles
extern int motion_torque_loop_handle;
extern int motion_vel_loop_handle;
extern int motion_pos_loop_handle;
extern int motion_test_torquebs_handle;

void init_motion_state_machine(motion_state_machine_t *motion_state_machine)
{
    motion_state_machine->state                       = MOTION_INIT;
    motion_state_machine->event.idle_to_exit          = 0;
    motion_state_machine->event.idle_to_pos           = 0;
    motion_state_machine->event.idle_to_torque        = 0;
    motion_state_machine->event.idle_to_vel           = 0;
    motion_state_machine->event.init_to_poweron       = 0;
    motion_state_machine->event.pos_to_idle           = 0;
    motion_state_machine->event.torque_to_idle        = 0;
    motion_state_machine->event.vel_to_idle           = 0;
    motion_state_machine->event.idle_to_test_torquebs = 0;
    motion_state_machine->event.test_torquebs_to_idle = 0;
}

void update_motion_state_machine(motion_state_machine_t *motion_state_machine)
{
    switch (motion_state_machine->state) {
        case MOTION_INIT:
            // init motion state(maybe init controller)
            init_action(&motor1);
            if (motion_state_machine->event.init_to_poweron == 1) {
                motion_state_machine->state                 = MOTION_POWERON;
                motion_state_machine->event.init_to_poweron = 0;
                init_to_poweron_action(&motor1);
            }
            break;
        case MOTION_POWERON:
            poweron_action(&motor1);
            motion_state_machine->state = MOTION_IDLE;
            break;
        case MOTION_IDLE:
            idle_action(&motor1);
            if (motion_state_machine->event.idle_to_exit == 1) {
                motion_state_machine->state              = MOTION_EXIT;
                motion_state_machine->event.idle_to_exit = 0;
                idle_to_exit_action(&motor1);
            } else if (motion_state_machine->event.idle_to_pos == 1) {
                motion_state_machine->state             = MOTION_POSMODE;
                motion_state_machine->event.idle_to_pos = 0;
                idle_to_pos_action(&motor1);
            } else if (motion_state_machine->event.idle_to_vel == 1) {
                motion_state_machine->state             = MOTION_VELMODE;
                motion_state_machine->event.idle_to_vel = 0;
                idle_to_vel_action(&motor1);
            } else if (motion_state_machine->event.idle_to_torque == 1) {
                motion_state_machine->state                = MOTION_TORQUEMODE;
                motion_state_machine->event.idle_to_torque = 0;
                idle_to_torque_action(&motor1);
            } else if (motion_state_machine->event.idle_to_test_torquebs == 1) {
                motion_state_machine->state                       = TestMode_TorqueBS;
                motion_state_machine->event.idle_to_test_torquebs = 0;
                idle_to_test_torquebs_action(&motor1);
            }
            break;
        case MOTION_EXIT:
            exit_action(&motor1);
            break;
        case MOTION_POSMODE:
            posmode_action(&motor1);
            if (motion_state_machine->event.pos_to_idle == 1) {
                motion_state_machine->state             = MOTION_IDLE;
                motion_state_machine->event.pos_to_idle = 0;
                pos_to_idle_action(&motor1);
            }
            break;
        case MOTION_VELMODE:
            velmode_action(&motor1);
            if (motion_state_machine->event.vel_to_idle == 1) {
                motion_state_machine->state             = MOTION_IDLE;
                motion_state_machine->event.vel_to_idle = 0;
                vel_to_idle_action(&motor1);
            }
            break;
        case MOTION_TORQUEMODE:
            torquemode_action(&motor1);
            if (motion_state_machine->event.torque_to_idle == 1) {
                motion_state_machine->state                = MOTION_IDLE;
                motion_state_machine->event.torque_to_idle = 0;
                torque_to_idle_action(&motor1);
            }
            break;
        case TestMode_TorqueBS:
            testmode_torquebs_action(&motor1);
            if (motion_state_machine->event.test_torquebs_to_idle == 1) {
                motion_state_machine->state                       = MOTION_IDLE;
                motion_state_machine->event.test_torquebs_to_idle = 0;
                test_torquebs_to_idle_action(&motor1);
            }
            break;
        default:
            break;
    }
}

/* ============= STATE ACTIONS ============= */

void init_action(motor_t *motor)
{
    // clear the motor command
    motor->motor_param->target_torque = 0;
    set_dac_value(DAC_A, torque_permillage_to_dac(0));
    // clear test command
    excitation_signal = 0;
    // stop all control loops
    task_scheduler_disable_task(motion_torque_loop_handle);
    task_scheduler_disable_task(motion_vel_loop_handle);
    task_scheduler_disable_task(motion_pos_loop_handle);
    task_scheduler_disable_task(motion_test_torquebs_handle);
}

void poweron_action(motor_t *motor)
{
    // todo: enable the motor power, use digital io (24V)
}

void idle_action(motor_t *motor)
{
    init_action(motor);
}

void posmode_action(motor_t *motor)
{
}

void velmode_action(motor_t *motor)
{
    task_scheduler_enable_task(motion_vel_loop_handle);
}

void torquemode_action(motor_t *motor)
{
    task_scheduler_enable_task(motion_torque_loop_handle);
}

void exit_action(motor_t *motor)
{
    init_action(motor);
    // todo: decide if need to power off the motor and shutdown electric power
}

void testmode_torquebs_action(motor_t *motor)
{
    task_scheduler_enable_task(motion_test_torquebs_handle);
}

/* ============= STATE TRANSLATION ACTIONS ============= */

void init_to_poweron_action(motor_t *motor)
{
}

void idle_to_pos_action(motor_t *motor)
{
}

void idle_to_vel_action(motor_t *motor)
{
}

void idle_to_torque_action(motor_t *motor)
{
}

void pos_to_idle_action(motor_t *motor)
{
}

void vel_to_idle_action(motor_t *motor)
{
}

void torque_to_idle_action(motor_t *motor)
{
}

void idle_to_exit_action(motor_t *motor)
{
}

void idle_to_test_torquebs_action(motor_t *motor)
{
}

void test_torquebs_to_idle_action(motor_t *motor)
{
}
