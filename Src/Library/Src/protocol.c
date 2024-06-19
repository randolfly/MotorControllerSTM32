#include "protocol.h"
#include <string.h>
#include <stdio.h>

#ifdef TEST
protocol_frame_parser_t parser;
//~ dont directly use the recursive_buffer, use the parser.buf instead
uint8_t recursive_buffer[PROTOCOL_RECURSIVE_BUFFER_SIZE];
protocol_frame protocol_frame_parsed_result = {0};
#else
static protocol_frame_parser_t parser;
//~ dont directly use the recursive_buffer, use the parser.buf instead
static uint8_t recursive_buffer[PROTOCOL_RECURSIVE_BUFFER_SIZE];
static protocol_frame protocol_frame_parsed_result = {0};
#endif

static void EXTRACT_32BIT_4x8BIT(uint32_t raw_data, uint8_t *data_dest);
static void EXTRACT_16BIT_2x8BIT(uint16_t raw_data, uint8_t *data_dest);
static void EXTRACT_8BIT_1x8BIT(uint8_t raw_data, uint8_t *data_dest);
static uint8_t get_frame_data(uint8_t *buf, uint16_t r_ofs, unsigned int index);
static uint32_t get_frame_header(uint8_t *buf, uint16_t r_ofs);
static uint16_t get_frame_cmd(uint8_t *buf, uint16_t r_ofs);
static uint16_t get_frame_len(uint8_t *buf, uint16_t r_ofs);
static uint8_t get_frame_motor_id(uint8_t *buf, uint16_t r_ofs);
static uint8_t get_frame_checksum(uint8_t *buf, uint16_t r_ofs, uint16_t frame_len);

static int16_t find_frame_header(uint8_t *buf, uint16_t buf_len, uint16_t start, uint16_t target_len);
static uint16_t get_unparsed_frame_len(uint16_t frame_len, uint16_t buff_len, uint16_t start, uint16_t end);
static uint16_t protocol_frame_parse(uint8_t *data, uint16_t *data_len);
static void buf_put_data(uint8_t *buf, uint16_t ring_buf_len, uint16_t w_ofs, uint8_t *data, uint16_t data_len);
static void swap_cmd_header(uint8_t *cmd);
static void swap_cmd_length(uint8_t *cmd);
static void swap_cmd_type(uint8_t *cmd);

int32_t protocol_init(void)
{
    memset(&parser, 0, sizeof(protocol_frame_parser_t));
    parser.recursive_buffer_pointer = recursive_buffer;
    return 0;
}

void protocol_data_receive(uint8_t *data, uint16_t len)
{
    buf_put_data(parser.recursive_buffer_pointer,
                 PROTOCOL_RECURSIVE_BUFFER_SIZE,
                 parser.write_offset,
                 data,
                 len);
    parser.write_offset = (parser.write_offset + len) % PROTOCOL_RECURSIVE_BUFFER_SIZE;
}

int32_t protocol_data_handler(void)
{
    uint8_t frame_data[PROTOCOL_RECURSIVE_BUFFER_SIZE];
    uint16_t frame_len = 0;
    uint16_t cmd_type  = NULL_CMD;

    cmd_type = protocol_frame_parse(frame_data, &frame_len);
    switch (cmd_type) {
        case NULL_CMD: {

            printf("NULL_CMD\n");
            return NULL_CMD;
        }

        case SEND_VEL_PID_CMD: {

            printf("SEND_VEL_PID_CMD\n");
            return SEND_VEL_PID_CMD;
        }

        default:
            printf("default\n");
            return -1;
    }
}

uint8_t calculate_checksum(uint8_t init, uint8_t *ptr, uint8_t len)
{
    uint8_t sum = init;

    while (--len) {
        sum += *ptr;
        ptr++;
    }

    return sum;
}

void rearrange_cmd(uint8_t *cmd)
{
    swap_cmd_header(cmd);
    swap_cmd_length(cmd);
    swap_cmd_type(cmd);
}

void serialize_frame_data(uint8_t *data_dest, protocol_frame *frame)
{
    EXTRACT_32BIT_4x8BIT(frame->header, data_dest + FRAME_INDEX_HEAD);
    EXTRACT_8BIT_1x8BIT(frame->motor_id, data_dest + FRAME_INDEX_MOTOR_ID);
    EXTRACT_16BIT_2x8BIT(frame->len, data_dest + FRAME_INDEX_LEN);
    EXTRACT_16BIT_2x8BIT(frame->cmd, data_dest + FRAME_INDEX_CMD);
    // copy data
    memcpy(data_dest + PROTOCOL_FRAME_HEADER_SIZE,
           frame->data,
           frame->len - PROTOCOL_FRAME_HEADER_SIZE - PROTOCOL_FRAME_CHECKSUM_SIZE);
    // auto calculate checksum
    EXTRACT_8BIT_1x8BIT(0x00, data_dest + PROTOCOL_FRAME_HEADER_SIZE);
    frame->checksum           = calculate_checksum(0, data_dest, frame->len);
    data_dest[frame->len - 1] = frame->checksum;
}

void deserialize_frame_data_from_dest(uint8_t *data_dest, protocol_frame *frame)
{

    frame->header   = get_frame_header(data_dest, 0);
    frame->motor_id = get_frame_motor_id(data_dest, 0);
    frame->len      = get_frame_len(data_dest, 0);
    frame->cmd      = get_frame_cmd(data_dest, 0);
    // copy data
    memcpy(frame->data,
           data_dest + PROTOCOL_FRAME_HEADER_SIZE,
           frame->len - PROTOCOL_FRAME_HEADER_SIZE - PROTOCOL_FRAME_CHECKSUM_SIZE);
    frame->checksum = get_frame_checksum(data_dest, 0, frame->len);
}

void deserialize_frame_data(protocol_frame *frame)
{
    frame->header   = protocol_frame_parsed_result.header;
    frame->motor_id = protocol_frame_parsed_result.motor_id;
    frame->len      = protocol_frame_parsed_result.len;
    frame->cmd      = protocol_frame_parsed_result.cmd;
    memcpy(frame->data,
           protocol_frame_parsed_result.data,
           frame->len - PROTOCOL_FRAME_HEADER_SIZE - PROTOCOL_FRAME_CHECKSUM_SIZE);
    frame->checksum = protocol_frame_parsed_result.checksum;
}
/* =========== auxiliary functions ===========*/

/**
 * @brief extract 32bit data to 4x8 bit data array(low end first|pos 0)
 * @param  raw_data: 32bit raw data
 * @param  data_dest: data array destination
 */
static void EXTRACT_32BIT_4x8BIT(uint32_t raw_data, uint8_t *data_dest)
{
    data_dest[0] = (uint8_t)(raw_data & 0x000000FF);
    data_dest[1] = (uint8_t)((raw_data & 0x0000FF00) >> 8);
    data_dest[2] = (uint8_t)((raw_data & 0x00FF0000) >> 16);
    data_dest[3] = (uint8_t)((raw_data & 0xFF000000) >> 24);
}

/**
 * @brief extract 16bit data to 2x8 bit data array(low end first)
 * @param  raw_data: 16bit raw data
 * @param  data_dest: data array destination
 */
static void EXTRACT_16BIT_2x8BIT(uint16_t raw_data, uint8_t *data_dest)
{
    data_dest[0] = (uint8_t)(raw_data & 0x00FF);
    data_dest[1] = (uint8_t)((raw_data & 0xFF00) >> 8);
}
/**
 * @brief extract 8bit data to 1x8 bit data array(low end first)
 * @param  raw_data: 8bit raw data
 * @param  data_dest: data array destination
 */
static void EXTRACT_8BIT_1x8BIT(uint8_t raw_data, uint8_t *data_dest)
{
    data_dest[0] = (uint8_t)(raw_data & 0xFF);
}

/**
 * @brief Get the frame data object from recursive_buffer
 * @param  buf: pointer to the recursive buffer
 * @param  r_ofs: read offset of the frame
 * @param  index: index of the data in the frame
 * @return uint8_t: data value
 */
static uint8_t get_frame_data(uint8_t *buf, uint16_t r_ofs, unsigned int index)
{
    return buf[(r_ofs + index) % PROTOCOL_RECURSIVE_BUFFER_SIZE] & 0xFF;
}

/**
 * @brief Get the frame header object from recursive_buffer
 * @param  buf: pointer to the recursive buffer
 * @param  r_ofs: read offset of the frame
 * @return uint32_t: frame header value
 */
static uint32_t get_frame_header(uint8_t *buf, uint16_t r_ofs)
{
    return (get_frame_data(buf, r_ofs, FRAME_INDEX_HEAD + 0) << 0 |
            get_frame_data(buf, r_ofs, FRAME_INDEX_HEAD + 1) << 8 |
            get_frame_data(buf, r_ofs, FRAME_INDEX_HEAD + 2) << 16 |
            get_frame_data(buf, r_ofs, FRAME_INDEX_HEAD + 3) << 24);
}

/**
 * @brief Get the frame type(command)
 * @param  buf: pointer to the recursive buffer
 * @param  r_ofs: read offset of the frame
 * @return uint16_t: command value
 */
static uint16_t get_frame_cmd(uint8_t *buf, uint16_t r_ofs)
{
    return (get_frame_data(buf, r_ofs, FRAME_INDEX_CMD) << 0 |
            get_frame_data(buf, r_ofs, FRAME_INDEX_CMD + 1) << 8);
}

/**
 * @brief Get the frame len object(length)
 * @param  buf: pointer to the recursive buffer
 * @param  r_ofs: read offset of the frame
 * @return uint16_t: length value
 */
static uint16_t get_frame_len(uint8_t *buf, uint16_t r_ofs)
{
    return (get_frame_data(buf, r_ofs, FRAME_INDEX_LEN) << 0 |
            get_frame_data(buf, r_ofs, FRAME_INDEX_LEN + 1) << 8);
}

/**
 * @brief Get the frame motor id object
 * @param  buf: pointer to the recursive buffer
 * @param  r_ofs: read offset of the frame
 * @return uint8_t: motor id value
 */
static uint8_t get_frame_motor_id(uint8_t *buf, uint16_t r_ofs)
{
    return get_frame_data(buf, r_ofs, FRAME_INDEX_MOTOR_ID);
}

/**
 * @brief Get the frame checksum object(CRC-16)
 * @param  buf: pointer to the recursive buffer
 * @param  r_ofs: read offset of the frame
 * @param  frame_len: frame length
 * @return uint8_t: checksum value
 */
static uint8_t get_frame_checksum(uint8_t *buf, uint16_t r_ofs, uint16_t frame_len)
{
    return get_frame_data(buf, r_ofs, frame_len - 1);
}

/**
 * @brief find frame header in the buffer
 * @param  buf: pointer to the buffer
 * @param  buf_len: buffer length
 * @param  start: start index of the buffer
 * @param  target_len: target length of the frame(need to find)
 * @return int16_t: -1: not found, other: found index
 */
static int16_t find_frame_header(uint8_t *buf, uint16_t buf_len, uint16_t start, uint16_t target_len)
{
    uint16_t i = 0;
    for (i = 0; i < (target_len - 3); i++) {
        if (((buf[(start + i + 0) % buf_len] << 0) |
             (buf[(start + i + 1) % buf_len] << 8) |
             (buf[(start + i + 2) % buf_len] << 16) |
             (buf[(start + i + 3) % buf_len] << 24)) == PROTOCOL_FRAME_HEADER) {
            return ((start + i) % buf_len);
        }
    }
    return -1;
}

/**
 * @brief parse the frame
 * @param  data: frame data
 * @param  data_len: frame length
 * @return uint16_t: command value
 */
static uint16_t protocol_frame_parse(uint8_t *data, uint16_t *data_len)
{
    uint16_t cmd                     = NULL_CMD;
    protocol_frame_parsed_result.cmd = cmd;
    uint16_t unparsed_len            = 0;
    int16_t header_ofs               = -1;
    uint8_t checksum                 = 0;

    unparsed_len = get_unparsed_frame_len(parser.frame_len, PROTOCOL_RECURSIVE_BUFFER_SIZE, parser.read_offset, parser.write_offset);
    if (unparsed_len < PROTOCOL_FRAME_HEADER_SIZE) {
        return cmd;
    }

    // no frame header founded, continue found
    if (0 == parser.found_frame_head) {
        header_ofs = find_frame_header(parser.recursive_buffer_pointer,
                                       PROTOCOL_RECURSIVE_BUFFER_SIZE,
                                       parser.read_offset,
                                       unparsed_len);
        if (0 <= header_ofs) {
            // frame header founded
            parser.found_frame_head = 1;
            parser.read_offset      = header_ofs;

            // check if unparsed frame size >= ideal frame size
            if (get_unparsed_frame_len(parser.frame_len,
                                       PROTOCOL_RECURSIVE_BUFFER_SIZE,
                                       parser.read_offset,
                                       parser.write_offset) < PROTOCOL_FRAME_HEADER_SIZE) {
                return cmd;
            }
        } else {
            // no valid frame header in unparsed data, remove all data in this parse
            parser.read_offset = ((parser.read_offset + unparsed_len - 3) % PROTOCOL_RECURSIVE_BUFFER_SIZE);
            return cmd;
        }
    }

    // check frame length valid
    if (0 == parser.frame_len) {
        parser.frame_len = get_frame_len(parser.recursive_buffer_pointer, parser.read_offset);
        if (unparsed_len < parser.frame_len) {
            return cmd;
        }
    }

    // frame header valid, do checksum
    if ((parser.frame_len + parser.read_offset - PROTOCOL_FRAME_CHECKSUM_SIZE) > PROTOCOL_RECURSIVE_BUFFER_SIZE) {
        checksum = calculate_checksum(checksum, parser.recursive_buffer_pointer + parser.read_offset,
                                      PROTOCOL_RECURSIVE_BUFFER_SIZE - parser.read_offset);
        checksum = calculate_checksum(checksum, parser.recursive_buffer_pointer, parser.frame_len - PROTOCOL_FRAME_CHECKSUM_SIZE + parser.read_offset - PROTOCOL_RECURSIVE_BUFFER_SIZE);
    } else {
        checksum = calculate_checksum(checksum, parser.recursive_buffer_pointer + parser.read_offset, parser.frame_len - PROTOCOL_RECURSIVE_BUFFER_SIZE);
    }

    uint8_t tmp_checksum = 0;
    tmp_checksum         = get_frame_checksum(parser.recursive_buffer_pointer,
                                              parser.read_offset,
                                              parser.frame_len);
    if (checksum == tmp_checksum) {
        // all data valid
        if ((parser.read_offset + parser.frame_len) > PROTOCOL_RECURSIVE_BUFFER_SIZE) {
            uint16_t data_len_part = PROTOCOL_RECURSIVE_BUFFER_SIZE - parser.read_offset;
            memcpy(data, parser.recursive_buffer_pointer + parser.read_offset, data_len_part);
            memcpy(data + data_len_part, parser.recursive_buffer_pointer, parser.frame_len - data_len_part);
        } else {
            memcpy(data, parser.recursive_buffer_pointer + parser.read_offset, parser.frame_len);
        }
        *data_len = parser.frame_len;
        cmd       = get_frame_cmd(parser.recursive_buffer_pointer, parser.read_offset);
        deserialize_frame_data_from_dest(parser.recursive_buffer_pointer + parser.read_offset,
                                         &protocol_frame_parsed_result);
        parser.read_offset = (parser.read_offset + parser.frame_len) % PROTOCOL_RECURSIVE_BUFFER_SIZE;
    } else {
        // check error, update read_offset
        parser.read_offset = (parser.read_offset + 1) % PROTOCOL_RECURSIVE_BUFFER_SIZE;
    }
    parser.frame_len        = 0;
    parser.found_frame_head = 0;

    return cmd;
}

/**
 * @brief Get the unparsed frame length
 * @param  frame_len: ideal frame length
 * @param  buff_len: ring buffer length
 * @param  start: start parse index in ring buffer
 * @param  end: end parse index in ring buffer
 * @return uint16_t: unparsed frame length, 0: error
 */
static uint16_t get_unparsed_frame_len(uint16_t frame_len, uint16_t buff_len, uint16_t start, uint16_t end)
{
    uint16_t unparsed_len = 0;
    if (start <= end) {
        unparsed_len = end - start;
    } else {
        unparsed_len = buff_len - start + end;
    }

    if (frame_len > unparsed_len) {
        return 0;
    } else {
        return unparsed_len;
    }
}

/**
 * @brief write the data into the ring buffer
 * @param  buf: ring buffer pointer
 * @param  ring_buf_len: ring buffer max length
 * @param  w_ofs: write offset
 * @param  data: target data
 * @param  data_len: data length
 */
static void buf_put_data(uint8_t *buf, uint16_t ring_buf_len, uint16_t w_ofs,
                         uint8_t *data, uint16_t data_len)
{
    if ((w_ofs + data_len) > ring_buf_len) {
        uint16_t data_len_part = ring_buf_len - w_ofs;
        memcpy(buf + w_ofs, data, data_len_part);
        memcpy(buf, data + data_len_part, data_len - data_len_part);
    } else
        memcpy(buf + w_ofs, data, data_len);
}

/**
 * @brief swap cmd header in data array
 * @param  cmd: data array
 */
static void swap_cmd_header(uint8_t *cmd)
{
    uint8_t tmp               = 0;
    tmp                       = cmd[FRAME_INDEX_HEAD + 0];
    cmd[FRAME_INDEX_HEAD + 0] = cmd[FRAME_INDEX_HEAD + 3];
    cmd[FRAME_INDEX_HEAD + 3] = tmp;

    tmp                       = cmd[FRAME_INDEX_HEAD + 2];
    cmd[FRAME_INDEX_HEAD + 2] = cmd[FRAME_INDEX_HEAD + 1];
    cmd[FRAME_INDEX_HEAD + 1] = tmp;
}

/**
 * @brief swap cmd length in data array
 * @param  cmd: data array
 */
static void swap_cmd_length(uint8_t *cmd)
{
    uint8_t tmp              = 0;
    tmp                      = cmd[FRAME_INDEX_LEN + 0];
    cmd[FRAME_INDEX_LEN + 0] = cmd[FRAME_INDEX_LEN + 1];
    cmd[FRAME_INDEX_LEN + 1] = tmp;
}

/**
 * @brief swap cmd type in data array
 * @param  cmd: data array
 */
static void swap_cmd_type(uint8_t *cmd)
{
    uint8_t tmp              = 0;
    tmp                      = cmd[FRAME_INDEX_CMD + 0];
    cmd[FRAME_INDEX_CMD + 0] = cmd[FRAME_INDEX_CMD + 1];
    cmd[FRAME_INDEX_CMD + 1] = tmp;
}