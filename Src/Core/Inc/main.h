/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define STATE_TIM_PRESCALER 120-1
#define STATE_TIM_COUNTER_MAX 100-1
#define ENCODER_RESOLUTION (63000 * 1024)
#define ENCODER_A_Pin GPIO_PIN_10
#define ENCODER_A_GPIO_Port GPIOH
#define ENCODER_B_Pin GPIO_PIN_11
#define ENCODER_B_GPIO_Port GPIOH
#define DATALOG_UART_TX_Pin GPIO_PIN_8
#define DATALOG_UART_TX_GPIO_Port GPIOD
#define DATALOG_UART_RX_Pin GPIO_PIN_9
#define DATALOG_UART_RX_GPIO_Port GPIOD
#define LED_1_Pin GPIO_PIN_15
#define LED_1_GPIO_Port GPIOA
#define COMMAND_UART_TX_Pin GPIO_PIN_6
#define COMMAND_UART_TX_GPIO_Port GPIOB
#define COMMAND_UART_RX_Pin GPIO_PIN_7
#define COMMAND_UART_RX_GPIO_Port GPIOB
#define ENCODER_Z_Pin GPIO_PIN_7
#define ENCODER_Z_GPIO_Port GPIOI
#define ENCODER_Z_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */
// time4: state machine timer-> 240M/120/100 = 20KHz
// hence max freq is 20kHz, ideal ticks is 20k/target_freq, unit Hz
#define GET_TASK_SCHEDULER_IDEAL_TICKS(target_freq) (20000 / target_freq)
// max 20 tasks in the task scheduler
#define TASK_SCHEDULER_MAX_TASK 20

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
