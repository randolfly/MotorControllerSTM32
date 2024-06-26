/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    usart.h
 * @brief   This file contains all the function prototypes for
 *          the usart.c file
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
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "protocol.h"
#include "byte_operator.h"
/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart3;

/* USER CODE BEGIN Private defines */
extern protocol_frame receive_frame;
extern protocol_frame send_frame;

extern char param_name_string_array[PROTOCOL_FRAME_MAX_SIZE];
extern uint8_t param_data_array[PROTOCOL_FRAME_MAX_SIZE];

#define UART_PROTOCOL huart1
#define UART_DATA     huart3
/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);
void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */
/**
 * @brief send (protocol)frame data by uart dma
 * @param  frame: single protocol frame data
 */
void Send_Protocol_Frame_Data(protocol_frame *frame);

/**
 * @brief start uart receive dma frames
 */
void Start_Protocol_Frame_Receive(void);

/**
 * @brief parse protocol uart frame
 */
void Parse_Protocol_Frame(void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

