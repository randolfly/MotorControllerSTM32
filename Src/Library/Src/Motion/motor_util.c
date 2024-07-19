#include "Motion/motor_util.h"

#ifdef NON_STM32
#define PWM_TIM_COUNTER_MAX 2000 - 1

#endif // NON_STM32

uint16_t torque_permillage_to_dac(double torque_permillage)
{
    if (torque_permillage > 1000.0) {
        torque_permillage = 1000.0;
    } else if (torque_permillage < -1000.0) {
        torque_permillage = -1000.0;
    }

    return (uint16_t)(torque_permillage * (double)(0xFFFF) / 2000.0 + (double)(0xFFFF) / 2.0);
}

uint16_t torque_permillage_to_pwm(double torque_permillage)
{
    if (torque_permillage > 980.0) {
        torque_permillage = 980.0;
    } else if (torque_permillage < -980.0) {
        torque_permillage = -980.0;
    }
    return ((int)(torque_permillage)) + (PWM_TIM_COUNTER_MAX + 1) / 2;
    // return (uint16_t)(torque_permillage * (double)(PWM_TIM_COUNTER_MAX) / 2000.0 + (double)(PWM_TIM_COUNTER_MAX) / 2.0);
}