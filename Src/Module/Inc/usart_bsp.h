/**
 * @file usart_bsp.h
 * @brief the bsp file for usart, which provides the usart control functions
 * @details the usart is used for the command and datalog communication
 * @author randolf (1665718426@qq.com)
 * @version 1.0.1
 * @date 2024-07-15
 *
 * @copyright Copyright (c) 2024  randolf
 *
 */
#ifndef __USART_BSP_H__
#define __USART_BSP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "usart.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include "Protocol/protocol_parser.h"
#include "Util/byte_operator.h"

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

/**
 * @brief init the command protocol parser
 */
void Init_Command_Protocol_Parser(void);

/**
 * @brief de-init the command protocol parser
 */
void DeInit_Command_Protocol_Parser(void);

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

#ifdef __cplusplus
}
#endif

#endif // __USART_BSP_H__