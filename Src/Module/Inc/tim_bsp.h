/**
 * @file tim_bsp.h
 * @brief the bsp file for tim, which provides the timer control functions
 * @details the tim is used for the task scheduler and encoder timer
 * @author randolf (1665718426@qq.com)
 * @version 1.0.1
 * @date 2024-07-15
 *
 * @copyright Copyright (c) 2024  randolf
 *
 */
#ifndef __TIM_BSP_H__
#define __TIM_BSP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "tim.h"

#define PWM_TIMER            htim1
#define ENCODER_TIMER        htim5
#define TASK_SCHEDULER_TIMER htim4

/**
 * @brief start the system state timer
 */
void Start_Task_Scheduler_Timer(void);

/**
 * @brief start the encoder timer
 */
void Start_Encoder_Timer(void);

/**
 * @brief start the pwm output
 */
void Start_PWM_Timer(void);

/**
 * @brief set the pwm compare value, modify pwm duty cycle
 * @param  pwm_value: compare value
 */
void Set_PWM_Value(uint16_t pwm_value);

/**
 * @brief initialize the task scheduler
 */
void Init_Task_Scheduler(void);

/**
 * @brief de-initialize the task scheduler
 */
void DeInit_Task_Scheduler(void);

#ifdef __cplusplus
}
#endif

#endif // __TIM_BSP_H__