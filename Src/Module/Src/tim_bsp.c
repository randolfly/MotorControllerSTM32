#include "tim_bsp.h"
#include "Util/task_scheduler.h"

/// @brief timer interrupt callback function(20kHz), used for task scheduler
/// @param htim
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &TASK_SCHEDULER_TIMER) {
        task_scheduler_tick();
    }
}

void Start_Task_Scheduler_Timer()
{
    HAL_TIM_Base_Start_IT(&TASK_SCHEDULER_TIMER);
}

void Start_Encoder_Timer(void)
{
    HAL_TIM_Encoder_Start(&ENCODER_TIMER, TIM_CHANNEL_ALL); // start the encoder timer
}

void Start_PWM_Timer(void)
{
    HAL_TIM_PWM_Start(&PWM_TIMER, TIM_CHANNEL_1); // pwm channel 1->motor1 pwm channel
}

void Set_PWM_Value(uint16_t pwm_value)
{
    if (pwm_value > PWM_TIM_COUNTER_MAX - 1) {
        pwm_value = PWM_TIM_COUNTER_MAX - 1;
    }
    __HAL_TIM_SET_COMPARE(&PWM_TIMER, TIM_CHANNEL_1, pwm_value);
}

void Init_Task_Scheduler(void)
{
    init_task_scheduler(TASK_SCHEDULER_MAX_TASK);
}

void DeInit_Task_Scheduler(void)
{
    deinit_task_scheduler();
}