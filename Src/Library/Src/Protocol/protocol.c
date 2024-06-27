#include "Protocol/protocol.h"
#include <stdio.h>

void set_frame_data(protocol_frame_t *frame, uint8_t *data, uint16_t data_len)
{
    frame->data = data;
    frame->len  = PROTOCOL_FRAME_HEADER_SIZE + data_len + PROTOCOL_FRAME_CHECKSUM_SIZE;
}

void serialize_frame_data(uint8_t *data_dest, protocol_frame_t *frame)
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
    frame->checksum                                      = calculate_checksum(0, data_dest, frame->len - PROTOCOL_FRAME_CHECKSUM_SIZE);
    data_dest[frame->len - PROTOCOL_FRAME_CHECKSUM_SIZE] = frame->checksum;
}

void deserialize_frame_data(uint8_t *data_src, protocol_frame_t *frame)
{
    frame->header   = get_frame_header(data_src, 0);
    frame->motor_id = get_frame_motor_id(data_src, 0);
    frame->len      = get_frame_len(data_src, 0);
    frame->cmd      = get_frame_cmd(data_src, 0);
    // copy data
    memcpy(frame->data,
           data_src + PROTOCOL_FRAME_HEADER_SIZE,
           frame->len - PROTOCOL_FRAME_HEADER_SIZE - PROTOCOL_FRAME_CHECKSUM_SIZE);
    frame->checksum = get_frame_checksum(data_src, 0, frame->len);
}

uint8_t calculate_checksum(uint8_t init, uint8_t *ptr, uint8_t len)
{
    uint8_t sum = init;

    while (len--) {
        sum += *ptr;
        ptr++;
    }

    return sum;
}

void deep_copy_frame(protocol_frame_t *dest, protocol_frame_t *src)
{
    dest->header             = src->header;
    dest->motor_id           = src->motor_id;
    dest->len                = src->len;
    dest->cmd                = src->cmd;
    uint16_t param_data_size = src->len - PROTOCOL_FRAME_HEADER_SIZE - PROTOCOL_FRAME_CHECKSUM_SIZE;
    if (param_data_size > 0) {
        memcpy(dest->data, src->data, param_data_size);
    }
    dest->checksum = src->checksum;
}

/* =========== auxiliary functions ===========*/

void EXTRACT_32BIT_4x8BIT(uint32_t raw_data, uint8_t *data_dest)
{
    data_dest[0] = (uint8_t)(raw_data & 0x000000FF);
    data_dest[1] = (uint8_t)((raw_data & 0x0000FF00) >> 8);
    data_dest[2] = (uint8_t)((raw_data & 0x00FF0000) >> 16);
    data_dest[3] = (uint8_t)((raw_data & 0xFF000000) >> 24);
}

void EXTRACT_16BIT_2x8BIT(uint16_t raw_data, uint8_t *data_dest)
{
    data_dest[0] = (uint8_t)(raw_data & 0x00FF);
    data_dest[1] = (uint8_t)((raw_data & 0xFF00) >> 8);
}

void EXTRACT_8BIT_1x8BIT(uint8_t raw_data, uint8_t *data_dest)
{
    data_dest[0] = (uint8_t)(raw_data & 0xFF);
}

uint32_t get_frame_header(uint8_t *buf, uint16_t r_ofs)
{
    return (buf[r_ofs + FRAME_INDEX_HEAD + 0] << 0 |
            buf[r_ofs + FRAME_INDEX_HEAD + 1] << 8 |
            buf[r_ofs + FRAME_INDEX_HEAD + 2] << 16 |
            buf[r_ofs + FRAME_INDEX_HEAD + 3] << 24);
}

uint16_t get_frame_cmd(uint8_t *buf, uint16_t r_ofs)
{
    return (buf[r_ofs + FRAME_INDEX_CMD + 0] << 0 |
            buf[r_ofs + FRAME_INDEX_CMD + 1] << 8);
}

uint16_t get_frame_len(uint8_t *buf, uint16_t r_ofs)
{
    return (buf[r_ofs + FRAME_INDEX_LEN + 0] << 0 |
            buf[r_ofs + FRAME_INDEX_LEN + 1] << 8);
}

uint8_t get_frame_motor_id(uint8_t *buf, uint16_t r_ofs)
{
    return buf[r_ofs + FRAME_INDEX_MOTOR_ID + 0];
}

uint8_t get_frame_checksum(uint8_t *buf, uint16_t r_ofs, uint16_t frame_len)
{
    return buf[r_ofs + frame_len - 1];
}
