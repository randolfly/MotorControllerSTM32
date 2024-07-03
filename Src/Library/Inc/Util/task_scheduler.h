#ifndef __TASK_SCHEDULER_H__
#define __TASK_SCHEDULER_H__

#include <stdlib.h>
#include "Util/type_def_protocol.h"

#ifdef STM32H743xx
#include "main.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*task_func_t)(void);

/**
 * @brief initialize task scheduler with specified task nums
 * @param  task_size: max amount of tasks
 */
void init_task_scheduler(uint32_t task_size);

/**
 * @brief deinitialize task scheduler
 */
void deinit_task_scheduler(void);

/**
 * @brief run in main loop to execute tasks
 */
void task_scheduler_run(void);

/**
 * @brief  add task to task scheduler with specified period and enable
 * @param  task: task function
 * @param  period: period time(unit: task_scheduler_tick)
 * @param  enable: enable flag, 1->start immediately, 0->non-start
 * @return int: -1: add failed, N: task id
 */
int task_scheduler_add_task(task_func_t task, uint32_t period, uint8_t enable);

/**
 * @brief based on the tick, execute tasks
 */
void task_scheduler_tick(void);

/**
 * @brief start task with specified id
 * @param  task_id: task id
 */
void task_scheduler_enable_task(uint32_t task_id);

/**
 * @brief stop task with specified id
 * @param  task_id: task id
 */
void task_scheduler_disable_task(uint32_t task_id);

#ifdef _cplusplus
}
#endif
#endif // !__TASK_SCHEDULER_H__
