#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "Util/type_def_protocol.h"

#ifdef STM32H743xx
#include "main.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define ENCODER_RESOLUTION 63000 * 1024 /* encoder resolution*/
typedef struct {
    double_t start_position;
} encoder_config_t;

typedef struct
{
    int32_t rotation_num;              /* encoder rotation number, updated by Z signal */
    uint32_t current_revolute_counter; /* current encoder counter, indicates the locatin of single round */
    double_t position;                 /* encoder position(rad) */
    double_t velocity;                 /* encoder velocity(rad/s) */
    double_t acceleration;             /* encoder acceleration(rad/s^2) */
    encoder_config_t *encoder_config;  /* encoder configuration */
} encoder_t;

/**
 * @brief init encoder with specified configuration
 * @param  encoder: encoder object
 * @param  encoder_config: encoder configuration
 */
void encoder_init(encoder_t *encoder, encoder_config_t *encoder_config);

/**
 * @brief update encoder counter, position, velocity and acceleration
 * @param  encoder: encoder object
 * @param  encoder_counter: current encoder counter(get from __HAL_TIM_GET_COUNTER(&htim5))
 */
void encoder_update(encoder_t *encoder, uint32_t encoder_counter);
// todo: check encoder velocity calculation method paper
// should add fpu to accelerate execution?

#ifdef _cplusplus
}
#endif
#endif // !__ENCODER_H__