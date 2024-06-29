/**
 * @file motor.h
 * @brief provide the motor control functions
 * @author randolf (1665718426@qq.com)
 * @version 1.0.1
 * @date 2024-06-26
 *
 * @copyright Copyright (c) 2024  randolf
 *
 */
#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "Motion/motor_util.h"
#include "Motion/encoder.h"
#include "Motion/safety.h"

#ifdef STM32H743xx
#include "main.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    /* data region */
    float target_torque; /* target torque executed(Nm), clock-wise -> + */
    float actual_torque; /* actual torque */

    /* hardware(wire-pin, sensor) region */
    encoder_t encoder;

    /* config region */
    motion_config_t motion_config;
} motor_t;

typedef struct
{
    motion_limit_t motion_limit;
} motor_config_t;

/**
 * @brief init the motor
 * @param: target motor
 */
void motor_init(motor_t *motor);

/**
 * @brief turn on the electric power of motor(24V signal)
 * @param: motor: target motor
 */
void enable_motor_electric_power(motor_t *motor);

/**
 * @brief shut down the electric power of motor(24V signal)
 * @param motor: target motor
 */
void disable_motor_electric_power(motor_t *motor);

/**
 * @brief set the motor power on (the meaning in servo control)
 * @param  motor: target motor
 */
void poweron_motor(motor_t *motor);

/**
 * @brief set the motor power off (the meaning in servo control)
 * @param  motor: target motor
 */
void poweroff_motor(motor_t *motor);

/**
 * @brief set the target execution torque
 * @param  motor: target motor object
 * @param  target_torque: target torque(Nm), clock-wise is +
 */
void set_motor_torque(motor_t *motor, float target_torque);

#ifdef _cplusplus
}
#endif
#endif // !__MOTOR_H__