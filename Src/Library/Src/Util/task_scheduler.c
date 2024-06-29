#include "Util/task_scheduler.h"

typedef struct
{
    task_func_t task_func;
    uint64_t last_schedule, repeat;
    uint8_t enable;
} task_t;

static struct {
    uint64_t ticks;
    uint32_t task_nums;
    uint32_t tasks_size;
    task_t *tasks;
} task_scheduler;

void task_scheduler_init(uint32_t task_size)
{
    task_scheduler.ticks      = 0;
    task_scheduler.task_nums  = 0;
    task_scheduler.tasks_size = task_size * sizeof(task_t);
    task_scheduler.tasks      = (task_t *)malloc(task_scheduler.tasks_size);
}

void task_scheduler_deinit(void)
{
    free(task_scheduler.tasks);
}

void task_scheduler_tick(void)
{
    task_scheduler.ticks++;
}

void task_scheduler_run(void)
{
    for (uint32_t i = 0; i < task_scheduler.task_nums; i++) {
        if (task_scheduler.tasks[i].enable) {
            if (task_scheduler.ticks - task_scheduler.tasks[i].last_schedule >= task_scheduler.tasks[i].repeat) {
                task_scheduler.tasks[i].last_schedule = task_scheduler.ticks;
                task_scheduler.tasks[i].task_func();
            }
        }
    }
}

int task_scheduler_add_task(task_func_t task, uint32_t period, uint8_t enable)
{
    if (task_scheduler.task_nums < task_scheduler.tasks_size) {
        task_scheduler.tasks[task_scheduler.task_nums].task_func     = task;
        task_scheduler.tasks[task_scheduler.task_nums].last_schedule = task_scheduler.ticks - period;
        task_scheduler.tasks[task_scheduler.task_nums].repeat        = period;
        task_scheduler.tasks[task_scheduler.task_nums].enable        = enable;
        return task_scheduler.task_nums++;
    } else {
        return -1;
    }
}

void task_scheduler_enable_task(uint32_t task_id)
{
    if (task_id < task_scheduler.task_nums) {
        if (task_scheduler.tasks[task_id].enable == 0) {
            // start task immediately
            task_scheduler.tasks[task_id].last_schedule = task_scheduler.ticks - task_scheduler.tasks[task_id].repeat;
        }
        task_scheduler.tasks[task_id].enable = 1;
    }
}

void task_scheduler_disable_task(uint32_t task_id)
{
    if (task_id < task_scheduler.task_nums) {
        task_scheduler.tasks[task_id].enable = 0;
    }
}