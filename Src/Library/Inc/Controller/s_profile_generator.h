/**
 * @file s_profile_generator.h
 * @brief control the s profile generator model
 * @author randolf (1665718426@qq.com)
 * @version 1.0.1
 * @date 2024-07-17
 *
 * @copyright Copyright (c) 2024  randolf
 *
 */
#ifndef __S_PROFILE_GENERATOR_H__
#define __S_PROFILE_GENERATOR_H__

#include <stdlib.h>
#include "SProfileGenerator.h"

#include "Util/type_def_protocol.h"

#ifdef STM32H743xx
#include "main.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    // input
    double start_pos;
    double end_pos;
    double start_vel;
    double end_vel;
    double max_vel;
    double max_acc;
    double max_jerk;
    double execute;
    // output
    double pos;
} s_profile_generator_param_t;

typedef struct {
    SProfileGenerator_RT_MODEL *model;
    SProfileGenerator_DW *state;
    s_profile_generator_param_t *param;
} s_profile_generator_t;

/**
 * @brief init the model
 * @param  s_profile_generator
 */
void init_s_profile_generator(s_profile_generator_t *s_profile_generator);

/**
 * @brief deinit the model
 * @param  s_profile_generator
 */
void deinit_s_profile_generator(s_profile_generator_t *s_profile_generator);

/**
 * @brief execution 1 step of s profile generator
 * @param  s_profile_generator
 */
void step_s_profile_generator(s_profile_generator_t *s_profile_generator);

#ifdef _cplusplus
}
#endif
#endif // !__S_PROFILE_GENERATOR_H__