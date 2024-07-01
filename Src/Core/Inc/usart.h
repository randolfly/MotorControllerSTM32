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
#include <stdio.h>
#include "stdint.h"
#include <string.h>
#include <stdarg.h>
#include "Protocol/protocol_parser.h"
#include "Util/byte_operator.h"
/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart3;

/* USER CODE BEGIN Private defines */

/* ================== COMMAND ====================*/
extern protocol_frame_parser_t command_parser;
extern protocol_frame_t command_send_frame;
extern protocol_frame_t command_receive_frame;

extern char command_param_name_string_array[PROTOCOL_FRAME_MAX_SIZE];
extern uint8_t command_param_data_array[PROTOCOL_FRAME_MAX_SIZE];

/* ================== DATALOG ====================*/
extern protocol_frame_t datalog_send_frame;
extern float datalog_param_float_array[PROTOCOL_FRAME_MAX_SIZE];
extern uint8_t datalog_param_data_array[PROTOCOL_FRAME_MAX_SIZE];

#define UART_COMMAND huart1
#define UART_DATALOG huart3
/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);
void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */

/**
 * @brief send command (protocol)frame data by uart dma
 * @param  frame: single protocol frame data
 */
void Send_Command_Frame_Data(protocol_frame_t *frame);

/**
 * @brief start command uart receive dma frames
 */
void Start_Command_Frame_Receive(void);

/**
 * @brief parse protocol uart frame
 */
void Parse_Command_Frame(void);

/**
 * @brief send datalog (protocol)frame data by uart dma
 * @param  frame
 */
void Send_Datalog_Frame_Data(protocol_frame_t *frame);

/**
 * @brief relocate printf function to USART1
 * @param  ch character to be printed
 * @param  f file pointer
 * @return int
 */

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */
