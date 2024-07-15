/**
 * @file motor.h
 * @brief provide the motor control functions, which is isolated with the hardware
 * @details the motor is a model to control the motor motion based on the encoder feedback
 * @author randolf (1665718426@qq.com)
 * @version 1.0.1
 * @date 2024-06-26
 *
 * @copyright Copyright (c) 2024  randolf
 *
 */
#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <string.h>
#include <stdlib.h>
#include "Motion/motor_util.h"

#ifdef STM32H743xx
#include "main.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief init the motor
 * @param: target motor
 */
void init_motor(motor_t *motor);

/**
 * @brief deinit the motor
 * @param  motor
 */
void deinit_motor(motor_t *motor);

/**
 * @brief turn on the electric power of motor(24V signal)
 */
void enable_motor_electric_power();

/**
 * @brief shut down the electric power of motor(24V signal)
 */
void disable_motor_electric_power();

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

#ifdef _cplusplus
}
#endif
#endif // !__MOTOR_H__