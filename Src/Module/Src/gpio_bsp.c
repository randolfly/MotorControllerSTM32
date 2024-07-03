#include "gpio_bsp.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == ENCODER_Z_Pin) {
        HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
        __HAL_TIM_SET_COUNTER(&ENCODER_TIMER, 0);
        __HAL_GPIO_EXTI_CLEAR_IT(ENCODER_Z_Pin);
    }
}