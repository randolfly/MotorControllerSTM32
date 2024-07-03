#ifndef __TIM_BSP_H__
#define __TIM_BSP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "tim.h"

#include "Util/task_scheduler.h"

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