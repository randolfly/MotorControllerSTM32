#include "gpio_bsp.h"
#include "Controller/reset_zero_position.h"
#include "Motion/motor.h"

extern reset_zero_position_machine_t reset_zero_position_machine;
extern motor_t motor1;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == ENCODER_Z_Pin) {
        reset_zero_position_machine.param.ideal_zero_position = motor1.encoder->position;
        reset_zero_position_machine.event.reach_ideal_zero    = 1;
        // __HAL_TIM_SET_COUNTER(&ENCODER_TIMER, 0);
    }
}

void set_switch_ch1_on(void)
{
    HAL_GPIO_WritePin(GPIO_SWITCH_CH1_GPIO_Port, GPIO_SWITCH_CH1_Pin, GPIO_PIN_SET);
}

void set_switch_ch1_off(void)
{
    HAL_GPIO_WritePin(GPIO_SWITCH_CH1_GPIO_Port, GPIO_SWITCH_CH1_Pin, GPIO_PIN_RESET);
}

void set_switch_ch2_on(void)
{
    HAL_GPIO_WritePin(GPIO_SWITCH_CH2_GPIO_Port, GPIO_SWITCH_CH2_Pin, GPIO_PIN_SET);
}

void set_switch_ch2_off(void)
{
    HAL_GPIO_WritePin(GPIO_SWITCH_CH2_GPIO_Port, GPIO_SWITCH_CH2_Pin, GPIO_PIN_RESET);
}