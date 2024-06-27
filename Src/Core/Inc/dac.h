/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    dac.h
 * @brief   This file contains all the function prototypes for
 *          the dac.c file
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DAC_H__
#define __DAC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "Motion/motor_util.h"

#define DAC_MOTOR_COMMAND       hdac1
#define DAC_MOTOR_COMMAND_PORT1 DAC_CHANNEL_1
/* USER CODE END Includes */

extern DAC_HandleTypeDef hdac1;

/* USER CODE BEGIN Private defines */
extern uint32_t dac_value;

/* USER CODE END Private defines */

void MX_DAC1_Init(void);

/* USER CODE BEGIN Prototypes */

/**
 * @brief set motor torque value, range from -1000 to 1000, unit is permillage
 *  -1000->-max_torque, 0->0, 1000->max_torque
 * @param  torque_permillage: torque command in permillage
 */
void Set_Motor_Torque(float torque_permillage);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __DAC_H__ */
