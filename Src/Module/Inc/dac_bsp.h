#ifndef __DAC_BSP_H__
#define __DAC_BSP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "dac.h"
#include "Motion/motor_util.h"

#define DAC_MOTOR_COMMAND       hdac1
#define DAC_MOTOR_COMMAND_PORT1 DAC_CHANNEL_1

extern uint32_t dac_value;

/**
 * @brief set motor torque value, range from -1000 to 1000, unit is permillage
 *  -1000->-max_torque, 0->0, 1000->max_torque
 * @param  torque_permillage: torque command in permillage
 */
void Set_Motor_Torque(float torque_permillage);

#ifdef __cplusplus
}
#endif

#endif // __DAC_BSP_H__