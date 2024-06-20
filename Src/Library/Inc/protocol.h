/**
 * @file protocol.h
 * @brief contains the protocol of communication between the client and the server
 * @author randolf (1665718426@qq.com)
 * @version 1.0.1
 * @date 2024-06-18
 *
 * @copyright Copyright (c) 2024  randolf
 *
 */
#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

// defined for non-stm32 project
#include "type_def_protocol.h"
#include <string.h>

#ifdef STM32H743xx
#include "main.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief protocol frame structure
 */
typedef struct
{
    uint32_t header;  /* frame header */
    uint8_t motor_id; /* motor id */
    uint16_t len;     /* frame length */
    uint16_t cmd;     /* command */
    uint8_t *data;    /* frame data */
    uint8_t checksum; /* frame checksum*/
} protocol_frame;

typedef struct
{
    uint8_t *recursive_buffer_pointer;
    uint16_t read_offset;
    uint16_t write_offset;
    uint16_t frame_len;
    uint16_t found_frame_head;
} protocol_frame_parser_t;

// protocol recursive buffer size;
#define PROTOCOL_RECURSIVE_BUFFER_SIZE 256
// protocol frame checksum length
#define PROTOCOL_FRAME_CHECKSUM_SIZE 1

#define PROTOCOL_FRAME_HEADER_SIZE   9

#define PROTOCOL_FRAME_HEADER        0x0d000721

/* motor id definition*/
#define MOTOR_ID1 0x01
#define MOTOR_ID2 0x02

/* command definition */
/* client to server commands*/
#define SEND_VEL_PID_CMD  0x0001 // send pid command of velocity loop in client
#define SEND_POS_PID_CMD  0x0002 // send pid command of position loop in client
#define SEND_STATE_ID_CMD 0x0003 // send current system state id(statemachine) in client

/* server to client commands*/
#define SET_VEL_PID_CMD    0x1001 // set pid command of velocity loop in server
#define SET_POS_PID_CMD    0x1002 // set pid command of position loop in server
#define START_SYSTEM_CMD   0x1003 // start the system
#define STOP_SYSTEM_CMD    0x1004 // stop the system
#define EMERGENCY_STOP_CMD 0x1005 // emergency stop the system
#define RESET_SYSTEM_CMD   0x1006 // reset the system

/* null command*/
#define NULL_CMD 0xFFFF // null command

/* frame index definition */
#define FRAME_INDEX_HEAD     0x0u // frame head index
#define FRAME_INDEX_MOTOR_ID 0x4u // motor id index
#define FRAME_INDEX_LEN      0x5u // frame length index
#define FRAME_INDEX_CMD      0x7u // command index

// exchange 32bit data high and low bit
#define EXCHANGE_HIGH_LOW_BIT(data) ((((data) << 24) & 0xFF000000) | \
                                     (((data) << 8) & 0x00FF0000) |  \
                                     (((data) >> 8) & 0x0000FF00) |  \
                                     (((data) >> 24) & 0x000000FF))

/**
 * @brief serialize frame struct to uint8 data array, the checksum will be calculated automatically
 * @param  data_dest: target data array, only store 1 frame data, no need to protect the data array
 * @param  frame: frame struct
 */
void serialize_frame_data(uint8_t *data_dest, protocol_frame *frame);

/**
 * @brief deserialize frame struct from parser.recursive_buffer_pointer, the checksum will not be calculated
 * @param  frame: target frame struct
 */
void deserialize_frame_data(protocol_frame *frame);

/**
 * @brief deserialize frame struct from specified data array, the checksum will not be calculated
 * @param  data_dest: data array destination
 * @param  frame: target frame struct
 */
void deserialize_frame_data_from_dest(uint8_t *data_dest, protocol_frame *frame);

/**
 * @brief write the protocol data into recursive buffer
 * @param  data: target data array
 * @param  len: data length
 */
void protocol_data_receive(uint8_t *data, uint16_t len);

/**
 * @brief initialize the protocol
 * @return int32_t initialization result
 */
int32_t protocol_init(void);

/**
 * @brief process the received data
 * @return int32_t: process results
 *  -1 means unexpecetd result
 *  other is the command id
 */
int32_t protocol_data_handler(void);

/**
 * @brief calculate the checksum of the frame
 * @param  init: initial value of the checksum
 * @param  ptr: target data array
 * @param  len: data length
 * @return uint8_t: checksum value
 */
uint8_t calculate_checksum(uint8_t init, uint8_t *ptr, uint8_t len);

/**
 * @brief switch cmd array to the low end arrange type
 * @param  cmd: cmd data array
 */
void rearrange_cmd(uint8_t *cmd);

#ifdef _cplusplus
}
#endif

#endif // !__PROTOCOL_H__#pragma once
