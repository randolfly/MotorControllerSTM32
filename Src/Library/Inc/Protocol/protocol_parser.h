#ifndef __PROTOCOL_PARSER_H__
#define __PROTOCOL_PARSER_H__

// defined for non-stm32 project
#include "Util/type_def_protocol.h"
#include "Util/ringbuffer.h"
#include "Protocol/protocol.h"
#include <string.h>
#include <stdlib.h>

#ifdef STM32H743xx
#include "main.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    ring_buffer_t *ring_buffer; /** storage of ring_buffer */
    protocol_frame_t *frame;    /** storage of protocol_frame */
    uint8_t found_frame_head;
    uint16_t next_frame_len; /** next frame length, used as an indicator of */
} protocol_frame_parser_t;

#define PROTOCOL_RECURSIVE_BUFFER_SIZE 1024

/**
 * @brief initialize the protocol parser
 * @param parser: protocol_frame_parser instance
 */
void protocol_parser_init(protocol_frame_parser_t *parser);

/**
 * @brief deinitialize the protocol parser
 * @param  parser
 */
void protocol_parser_deinit(protocol_frame_parser_t *parser);

/**
 * @brief write the protocol data into parser recursive buffer
 * @param  parser: protocol_frame_parser instance
 * @param  data: target data array
 * @param  size: data length
 */
void protocol_data_receive(protocol_frame_parser_t *parser, uint8_t *data, uint32_t size);

/**
 * @brief process the received data
 * @param  parser: protocol_frame_parser instance
 */
uint16_t protocol_data_handler(protocol_frame_parser_t *parser);

/* =========== auxiliary functions ===========*/

/**
 * @brief find frame header in the buffer
 * @param  buffer: ringbuffer instance
 * @param  start: start index of the buffer
 * @param  target_len: target length of the frame(need to find)
 * @return int64_t: -1: not found, other: found index
 */
int64_t find_frame_header(ring_buffer_t *buffer, uint16_t start, uint16_t target_len);
/**
 * @brief parse the protocol ring buffer to get the frame raw data
 * @param  parser: protocol_frame_parser instance
 * @param  data_dest: target data array, used to store the frame raw data
 * @param  data_len: target data length, used to store the frame raw data length
 * @return uint16_t: frame cmd type
 */
uint16_t protocol_frame_parse(protocol_frame_parser_t *parser, uint8_t *data_dest, uint16_t *data_len);

/**
 * @brief Get the unparsed frame len in the ring buffer
 * @param  frame_len: ideal frame length
 * @param  buffer: ring buffer instance
 * @return uint16_t
 */
uint16_t get_unparsed_frame_len(uint16_t frame_len, ring_buffer_t *buffer);

/**
 * @brief the get_frame_len function for parser
 * @param  parser
 * @return uint16_t
 */
uint16_t get_frame_len_parser(protocol_frame_parser_t *parser);

/**
 * @brief the get_frame_checksum function for parser
 * @param  parser
 * @return uint16_t
 */
uint16_t get_frame_checksum_parser(protocol_frame_parser_t *parser);

/**
 * @brief store all the frame data into the data_dest
 * @param  parser: protocol_frame_parser instance
 * @param  data_dest: target data array
 */
void get_frame_full_data_parser(protocol_frame_parser_t *parser, uint8_t *data_dest);

/**
 * @brief the calculate_checksum function for parser
 * @param  parser
 * @return uint8_t
 */
uint8_t calculate_checksum_parser(protocol_frame_parser_t *parser);
#ifdef _cplusplus
}
#endif

#endif // !__PROTOCOL_PARSER_H__