#include "gpio_bsp.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == ENCODER_Z_Pin) {
        // todo: the Z signal is not simutaneous with A/B, causing cnt error
        HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
        // __HAL_TIM_SET_COUNTER(&ENCODER_TIMER, 0);
        __HAL_GPIO_EXTI_CLEAR_IT(ENCODER_Z_Pin);
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