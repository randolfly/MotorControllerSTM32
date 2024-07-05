/**
 * @file protocol.h
 * @brief contains the protocol of communication between the stm32 board and the computer
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
#include "Util/type_def_protocol.h"
#include "Util/ringbuffer.h"
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
} protocol_frame_t;

// protocol recursive buffer size;
#define PROTOCOL_FRAME_MAX_SIZE 100

/* frame index definition */
#define FRAME_INDEX_HEAD     0x0u // frame head index
#define FRAME_INDEX_MOTOR_ID 0x4u // motor id index
#define FRAME_INDEX_LEN      0x5u // frame length index
#define FRAME_INDEX_CMD      0x7u // command index

// protocol frame checksum length
#define PROTOCOL_FRAME_CHECKSUM_SIZE 1
#define PROTOCOL_FRAME_HEADER_SIZE   9

#define PROTOCOL_FRAME_HEADER        0x0d000721

/* motor id definition*/
#define MOTOR_ID1 0x01
#define MOTOR_ID2 0x02

/* command definition */

/* ========= CONTROL ============ */

/* ========= GET ============ */
#define GET_SYMBOL_DATA_CMD      0x1001 // get symbol data
#define GET_ECHO_SYMBOL_DATA_CMD 0x1101 // echo symbol data

/* ========= SET ============ */

#define SET_SYMBOL_DATA_CMD 0x2001 // set symbol data

/* ========= DATALOG ============ */

#define DATALOG_GET_AVAILABLE_DATA_CMD      0x3001 // check available log data
#define DATALOG_SET_LOG_DATA_CMD            0x3002 // set log data name
#define DATALOG_START_LOG_CMD               0x3003 // start log
#define DATALOG_STOP_LOG_CMD                0x3004 // stop log

#define DATALOG_ECHO_GET_AVAILABLE_DATA_CMD 0x3101 // send available log data
#define DATALOG_ECHO_SET_LOG_DATA_CMD       0x3102 // send all log data
#define DATALOG_RUNNING_CMD                 0x3103 // send in high-speed uart port

/* ========= OTHER ============ */
#define NULL_CMD 0xFFFF // null command

/**
 * @brief Set the frame param data, and update the frame length
 * @param  frame: frame struct
 * @param  data: byte array
 * @param  data_len: byte array length
 */
void set_frame_data(protocol_frame_t *frame, uint8_t *data, uint16_t data_len);

/**
 * @brief serialize frame struct to uint8 data array, the checksum will be calculated automatically
 * notice that this means the frame length should be properly treated, no automatic calculation
 * @param  data_dest: target data array, only store 1 frame data, no need to protect the data array
 * @param  frame: frame struct
 */
void serialize_frame_data(uint8_t *data_dest, protocol_frame_t *frame);

/**
 * @brief deserialize frame struct from specified data array
 * @param  data_src: source byte data array
 * @param  frame: target frame struct
 */
void deserialize_frame_data(uint8_t *data_src, protocol_frame_t *frame);

/**
 * @brief calculate the checksum of the frame
 * @param  init: initial value of the checksum
 * @param  ptr: target data array
 * @param  len: data length
 * @return uint8_t: checksum value
 */
uint8_t calculate_checksum(uint8_t init, uint8_t *ptr, uint8_t len);

/**
 * @brief deep copy the frame from src to dest
 * @param  dest: destination frame
 * @param  src: source frame
 */
void deep_copy_frame(protocol_frame_t *dest, protocol_frame_t *src);

/* =========== auxiliary functions ===========*/

/**
 * @brief extract 32bit data to 4x8 bit data array(low end first|pos 0)
 * @param  raw_data: 32bit raw data
 * @param  data_dest: data array destination
 */
void EXTRACT_32BIT_4x8BIT(uint32_t raw_data, uint8_t *data_dest);

/**
 * @brief extract 16bit data to 2x8 bit data array(low end first)
 * @param  raw_data: 16bit raw data
 * @param  data_dest: data array destination
 */
void EXTRACT_16BIT_2x8BIT(uint16_t raw_data, uint8_t *data_dest);

/**
 * @brief extract 8bit data to 1x8 bit data array(low end first)
 * @param  raw_data: 8bit raw data
 * @param  data_dest: data array destination
 */
void EXTRACT_8BIT_1x8BIT(uint8_t raw_data, uint8_t *data_dest);

/**
 * @brief Get the frame header object from byte array
 * @param  buf: byte array pointer
 * @param  r_ofs: read offset of the frame
 * @return uint32_t: frame header value
 */
uint32_t get_frame_header(uint8_t *buf, uint16_t r_ofs);

/**
 * @brief Get the frame cmd object from byte array
 * @param  buf: byte array pointer
 * @param  r_ofs: read offset of the frame
 * @return uint32_t: frame cmd value
 */
uint16_t get_frame_cmd(uint8_t *buf, uint16_t r_ofs);

/**
 * @brief Get the frame length object from byte array
 * @param  buf: byte array pointer
 * @param  r_ofs: read offset of the frame
 * @return uint32_t: frame length value
 */
uint16_t get_frame_len(uint8_t *buf, uint16_t r_ofs);

/**
 * @brief Get the frame motor id object from byte array
 * @param  buf: byte array pointer
 * @param  r_ofs: read offset of the frame
 * @return uint32_t: frame motor id value
 */
uint8_t get_frame_motor_id(uint8_t *buf, uint16_t r_ofs);

/**
 * @brief Get the frame checksum object(CRC-16) from byte array
 * @param  buf: pointer to the byte array
 * @param  r_ofs: read offset of the frame
 * @param  frame_len: frame length
 * @return uint8_t: checksum value
 */
uint8_t get_frame_checksum(uint8_t *buf, uint16_t r_ofs, uint16_t frame_len);

#ifdef _cplusplus
}
#endif

#endif // !__PROTOCOL_H__#pragma once
