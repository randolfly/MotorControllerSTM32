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
    protocol_frame_t *frame;    /** storage of current parsed protocol_frame */
    uint16_t frame_len;
    uint16_t found_frame_head;
} protocol_frame_parser_t;

#define PROTOCOL_RECURSIVE_BUFFER_SIZE 512

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
 * @brief retrive the parsed frame
 * @param  parser: protocol_frame_parser instance
 * @param  frame: protocol_frame instance
 */
void get_parsed_frame(protocol_frame_parser_t *parser, protocol_frame_t *frame);

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

/**
 * @brief deep copy the frame from src to dest
 * @param  dest: destination frame
 * @param  src: source frame
 */
void deep_copy_frame(protocol_frame_t *dest, protocol_frame_t *src);
/* =========== auxiliary functions ===========*/

static int32_t find_frame_header(uint8_t *buf, uint16_t buf_len, uint16_t start, uint16_t target_len);
static uint16_t get_unparsed_frame_len(uint16_t frame_len, uint16_t buff_len, uint16_t start, uint16_t end);
static uint16_t protocol_frame_parse(uint8_t *data, uint16_t *data_len);
static void buf_put_data(uint8_t *buf, uint16_t ring_buf_len, uint16_t w_ofs, uint8_t *data, uint16_t data_len);
static void swap_cmd_header(uint8_t *cmd);
static void swap_cmd_length(uint8_t *cmd);
static void swap_cmd_type(uint8_t *cmd);
#ifdef _cplusplus
}
#endif

#endif // !__PROTOCOL_PARSER_H__