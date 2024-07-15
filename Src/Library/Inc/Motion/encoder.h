/**
 * @file encoder.h
 * @brief this is a interface of encoder, which is isolated with motor motion parts
 * @details the encoder is a model to calculate the position, velocity and acceleration of encoder based on encoder counter
 * @author randolf (1665718426@qq.com)
 * @version 1.0.1
 * @date 2024-07-15
 *
 * @copyright Copyright (c) 2024  randolf
 *
 */
#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <math.h>
#include "Util/type_def_protocol.h"
#include "Controller/encoder_velocity_diff.h"

#ifdef STM32H743xx
#include "main.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    double_t start_position;
} encoder_config_t;

typedef struct
{
    /* data region */
    uint32_t last_counter;            /* last encoder counter */
    int32_t rotation_num;             /* encoder rotation num */
    double_t position;                /* encoder position(rad) */
    double_t velocity;                /* encoder velocity(rad/s) */
    double_t acceleration;            /* encoder acceleration(rad/s^2) */
    encoder_config_t *encoder_config; /* encoder configuration */

    /* method region */
    encoder_velocity_diff_t *velocity_diff_model; /* velocity diff model */
} encoder_t;

/**
 * @brief init encoder with specified configuration
 * @param  encoder: encoder object
 */
void init_encoder(encoder_t *encoder);

/**
 * @brief deinit encoder
 * @param  encoder
 */
void deinit_encoder(encoder_t *encoder);

/**
 * @brief update encoder counter, position, velocity and acceleration
 * @param  encoder: encoder object
 * @param  encoder_counter: current encoder counter(get from __HAL_TIM_GET_COUNTER(&htim5))
 */
void encoder_update(encoder_t *encoder, uint32_t encoder_counter);

#ifdef _cplusplus
}
#endif
#endif // !__ENCODER_H__