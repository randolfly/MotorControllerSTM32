#ifndef __PROTOCOL_PARSER_H__
#define __PROTOCOL_PARSER_H__

// defined for non-stm32 project
#include "type_def_protocol.h"
#include "ringbuffer.h"
#include "protocol.h"
#include <string.h>

#ifdef STM32H743xx
#include "main.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    ring_buffer_t *ring_buffer; /** storage of ring_buffer */
    uint16_t frame_len;
    uint16_t found_frame_head;
} protocol_frame_parser_t;

#define PROTOCOL_RECURSIVE_BUFFER_SIZE 512

/**
 * @brief initialize the protocol
 * @param parser: protocol_frame_parser instance
 * @param ring_buffer: protocol_frame ringbuffer instance
 */
void protocol_parser_init(protocol_frame_parser_t *parser, ring_buffer_t *ring_buffer);

/**
 * @brief deserialize frame struct from parser.recursive_buffer_pointer, the checksum will not be calculated
 * @param  frame: target frame struct
 */
void deserialize_frame_data(protocol_frame_t *frame);

/**
 * @brief write the protocol data into recursive buffer
 * @param  data: target data array
 * @param  len: data length
 */
void protocol_data_receive(uint8_t *data, uint16_t len);

/**
 * @brief process the received data
 * @return uint16_t: process results: cmd_type
 */
uint16_t protocol_data_handler(void);

#ifdef _cplusplus
}
#endif

#endif // !__PROTOCOL_PARSER_H__