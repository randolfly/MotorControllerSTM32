#include "Controller/reset_zero_position.h"
#include "Util/task_scheduler.h"
#include "Controller/motion_statemachine.h"
#include "Controller/s_profile_generator.h"

extern motion_state_machine_t msm;
extern s_profile_generator_t s_profile_generator;

void init_reset_zero_position_machine(reset_zero_position_machine_t *reset_zero_position_machine)
{
    reset_zero_position_machine->state                     = RESET_ZERO_HOLDON;
    reset_zero_position_machine->event.execute             = 0;
    reset_zero_position_machine->param.ideal_zero_position = 10;
    reset_zero_position_machine->param.target_velocity     = 0.5;
}

void update_reset_zero_position_machine(reset_zero_position_machine_t *reset_zero_position_machine, motor_t *motor)
{
    switch (reset_zero_position_machine->state) {
        case RESET_ZERO_HOLDON:
            holdon_action(reset_zero_position_machine, motor);
            if (reset_zero_position_machine->event.execute == 1) {
                reset_zero_position_machine->state         = RESET_ZERO_MOVEMENT;
                reset_zero_position_machine->event.execute = 0;
                holdon_to_movement_action(reset_zero_position_machine, motor);
            }
            break;
        case RESET_ZERO_MOVEMENT:
            movement_action(reset_zero_position_machine, motor);
            // note: update in gpio_bsp.c nvic callback
            if (reset_zero_position_machine->event.reach_ideal_zero == 1) {
                reset_zero_position_machine->state                  = RESET_ZERO_UPDATE_POS;
                reset_zero_position_machine->event.reach_ideal_zero = 0;
                movement_to_update_pos_action(reset_zero_position_machine, motor);
            }
            break;
        case RESET_ZERO_UPDATE_POS:
            update_pos_action(reset_zero_position_machine, motor);
            reset_zero_position_machine->state = RESET_ZERO_HOLDON;
        default:
            break;
    }
}

/* ============= STATE ACTIONS ============= */

void holdon_action(reset_zero_position_machine_t *reset_zero_position_machine, motor_t *motor)
{
    // reset_zero_position_machine->param.ideal_zero_position = 0;
}

void movement_action(reset_zero_position_machine_t *reset_zero_position_machine, motor_t *motor)
{
    motor->motor_param->target_velocity = reset_zero_position_machine->param.target_velocity;
}

void update_pos_action(reset_zero_position_machine_t *reset_zero_position_machine, motor_t *motor)
{
    // update pos
    motor->encoder->encoder_config->start_position += reset_zero_position_machine->param.ideal_zero_position;
    motor->motor_param->target_position = 0;
    s_profile_generator.param->end_pos  = 0;
    msm.event.idle_to_pos               = 1;
}

/* ============= STATE TRANSLATION ACTIONS ============= */

void holdon_to_movement_action(reset_zero_position_machine_t *reset_zero_position_machine, motor_t *motor)
{
    msm.event.pos_to_idle = 1;
    msm.event.idle_to_vel = 1;
}

void movement_to_update_pos_action(reset_zero_position_machine_t *reset_zero_position_machine, motor_t *motor)
{
    // stop motor
    motor->motor_param->target_velocity = 0;
    motor->motor_param->target_torque   = 0;
    msm.event.vel_to_idle               = 1;
}