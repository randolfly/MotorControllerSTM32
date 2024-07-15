/**
 * @file motion_statemachine.h
 * @brief this file is to define the motion state machine, and the state actions and state translation actions
 * @details the motion state machine is a finite state machine, which is used to control the motion of the motor
 * @author randolf (1665718426@qq.com)
 * @version 1.0.1
 * @date 2024-07-15
 *
 * @copyright Copyright (c) 2024  randolf
 *
 */
#ifndef __MOTION_STATEMACHINE_H__
#define __MOTION_STATEMACHINE_H__

#include <math.h>
#include "Util/type_def_protocol.h"
#include "Motion/motor.h"

#ifdef STM32H743xx
#include "main.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    MOTION_INIT,
    MOTION_POWERON,
    MOTION_IDLE,
    MOTION_POSMODE,
    MOTION_VELMODE,
    MOTION_TORQUEMODE,
    MOTION_EXIT,
    TestMode_TorqueBS,
} motion_state_t;

typedef struct {
    uint8_t init_to_poweron;
    uint8_t idle_to_pos;
    uint8_t idle_to_vel;
    uint8_t idle_to_torque;
    uint8_t pos_to_idle;
    uint8_t vel_to_idle;
    uint8_t torque_to_idle;
    uint8_t idle_to_exit;
    uint8_t test_torquebs_to_idle;
    uint8_t idle_to_test_torquebs;
} motion_event_t;

typedef struct {
    motion_state_t state;
    motion_event_t event;
} motion_state_machine_t;

extern motor_t motor1;

/**
 * @brief init the motion state machine with INIT state
 * @param  motion_state_machine
 */
void init_motion_state_machine(motion_state_machine_t *motion_state_machine);

/**
 * @brief update the motion state machine
 * @param  motion_state_machine
 */
void update_motion_state_machine(motion_state_machine_t *motion_state_machine);

/* ============= STATE ACTIONS ============= */

void init_action(motor_t *motor);

void poweron_action(motor_t *motor);

void idle_action(motor_t *motor);

void posmode_action(motor_t *motor);

void velmode_action(motor_t *motor);

void torquemode_action(motor_t *motor);

void exit_action(motor_t *motor);

void testmode_torquebs_action(motor_t *motor);

/* ============= STATE TRANSLATION ACTIONS ============= */

void init_to_poweron_action(motor_t *motor);

void idle_to_pos_action(motor_t *motor);

void idle_to_vel_action(motor_t *motor);

void idle_to_torque_action(motor_t *motor);

void pos_to_idle_action(motor_t *motor);

void vel_to_idle_action(motor_t *motor);

void torque_to_idle_action(motor_t *motor);

void idle_to_exit_action(motor_t *motor);

void idle_to_test_torquebs_action(motor_t *motor);

void test_torquebs_to_idle_action(motor_t *motor);

#ifdef _cplusplus
}
#endif
#endif // !__MOTION_STATEMACHINE_H__