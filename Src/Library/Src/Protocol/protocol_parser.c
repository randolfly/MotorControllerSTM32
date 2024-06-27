#include "Protocol/protocol_parser.h"

void protocol_parser_init(protocol_frame_parser_t *parser)
{
    parser->ring_buffer      = (ring_buffer_t *)malloc(sizeof(ring_buffer_t));
    parser->frame            = (protocol_frame_t *)malloc(sizeof(protocol_frame_t));
    parser->found_frame_head = 0;
    parser->frame_len        = 0;
    ring_buffer_init(parser->ring_buffer, PROTOCOL_RECURSIVE_BUFFER_SIZE);
}

void protocol_parser_deinit(protocol_frame_parser_t *parser)
{
    ring_buffer_deinit(parser->ring_buffer);
    free(parser->ring_buffer);
    free(parser->frame);
}

void get_parsed_frame(protocol_frame_parser_t *parser, protocol_frame_t *frame)
{
    deep_copy_frame(frame, parser->frame);
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
