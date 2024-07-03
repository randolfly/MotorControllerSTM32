#include "dac_bsp.h"

// send dac value to motor driver
uint32_t dac_value = 0;

void Set_Motor_Torque(float torque_permillage)
{
    dac_value = torque_permillage_to_dac(torque_permillage);
    HAL_DAC_SetValue(&DAC_MOTOR_COMMAND, DAC_MOTOR_COMMAND_PORT1, DAC_ALIGN_12B_R, dac_value);
    HAL_DAC_Start(&DAC_MOTOR_COMMAND, DAC_MOTOR_COMMAND_PORT1);
}