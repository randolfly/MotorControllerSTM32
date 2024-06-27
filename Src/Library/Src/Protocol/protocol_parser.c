#include "Protocol/protocol_parser.h"

void protocol_parser_init(protocol_frame_parser_t *parser)
{
    parser->ring_buffer = (ring_buffer_t *)malloc(sizeof(ring_buffer_t));
    ring_buffer_init(parser->ring_buffer, PROTOCOL_RECURSIVE_BUFFER_SIZE);
    parser->frame = (protocol_frame_t *)malloc(sizeof(protocol_frame_t));
    memset(parser->frame, 0, sizeof(protocol_frame_t));
    parser->frame->data = (uint8_t *)malloc(PROTOCOL_FRAME_MAX_SIZE);
    memset(parser->frame->data, 0, PROTOCOL_FRAME_MAX_SIZE);
    parser->found_frame_head = 0;
    parser->next_frame_len   = 0;
}

void protocol_parser_deinit(protocol_frame_parser_t *parser)
{
    ring_buffer_deinit(parser->ring_buffer);
    free(parser->ring_buffer);
    free(parser->frame->data);
    free(parser->frame);
}

void protocol_data_receive(protocol_frame_parser_t *parser, uint8_t *data, uint32_t size)
{
    ring_buffer_queue_arr(parser->ring_buffer, data, size);
}

uint16_t protocol_data_handler(protocol_frame_parser_t *parser)
{
    uint8_t frame_data[PROTOCOL_FRAME_MAX_SIZE];
    uint16_t frame_len = 0;
    uint16_t cmd_type  = NULL_CMD;

    cmd_type = protocol_frame_parse(parser, frame_data, &frame_len);

    return cmd_type;
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

int64_t find_frame_header(ring_buffer_t *buffer, uint16_t start, uint16_t target_len)
{
    uint32_t i = 0;
    uint8_t head_1, head_2, head_3, head_4;

    for (i = 0; i < (target_len - 3); i++) {
        ring_buffer_peek(buffer, &head_1, start + i + 0);
        ring_buffer_peek(buffer, &head_2, start + i + 1);
        ring_buffer_peek(buffer, &head_3, start + i + 2);
        ring_buffer_peek(buffer, &head_4, start + i + 3);
        if (((head_1 << 0) |
             (head_2 << 8) |
             (head_3 << 16) |
             (head_4 << 24)) == PROTOCOL_FRAME_HEADER) {
            return ((start + i) & RING_BUFFER_MASK(buffer));
        }
    }
    return -1;
}

uint16_t protocol_frame_parse(protocol_frame_parser_t *parser, uint8_t *data_dest, uint16_t *data_len)
{
    uint16_t cmd          = NULL_CMD;
    parser->frame->cmd    = cmd;
    uint16_t unparsed_len = 0;
    uint16_t header_ofs   = -1;

    unparsed_len = get_unparsed_frame_len(
        parser->next_frame_len, parser->ring_buffer);
    if (unparsed_len < PROTOCOL_FRAME_HEADER_SIZE) {
        return cmd;
    }

    // no frame header founded, continue found
    if (0 == parser->found_frame_head) {
        header_ofs = find_frame_header(parser->ring_buffer,
                                       0,
                                       unparsed_len);
        if (0 <= header_ofs) {
            // frame header founded
            parser->found_frame_head        = 1;
            parser->ring_buffer->tail_index = parser->ring_buffer->tail_index + header_ofs;

            // check if unparsed frame size >= ideal frame size
            if (get_unparsed_frame_len(parser->next_frame_len, parser->ring_buffer) < PROTOCOL_FRAME_HEADER_SIZE) {
                return cmd;
            }
        } else {
            // no valid frame header in unparsed data, remove all data in this parse
            parser->ring_buffer->tail_index = ((parser->ring_buffer->tail_index + unparsed_len - 3) & RING_BUFFER_MASK(parser->ring_buffer));
            return cmd;
        }
    }

    // check frame length valid
    if (0 == parser->next_frame_len) {
        parser->next_frame_len = get_frame_len_parser(parser);
        if (unparsed_len < parser->next_frame_len) {
            return cmd;
        }
    }

    // frame header valid, do checksum
    uint8_t checksum     = calculate_checksum_parser(parser);
    uint8_t tmp_checksum = get_frame_checksum_parser(parser);

    if (checksum == tmp_checksum) {
        // all data valid
        get_frame_full_data_parser(parser, data_dest);
        *data_len = parser->next_frame_len;
        cmd       = get_frame_cmd(data_dest, 0);
        deserialize_frame_data(data_dest, parser->frame);
    } else {
        // check error, update read_offset
        uint8_t tmp_data;
        ring_buffer_dequeue(parser->ring_buffer, &tmp_data);
    }
    parser->found_frame_head = 0;
    parser->next_frame_len   = 0;

    return cmd;
}

static uint16_t get_unparsed_frame_len(uint16_t frame_len, ring_buffer_t *buffer)
{
    uint16_t unparsed_len = ring_buffer_num_items(buffer);

    if (frame_len > unparsed_len) {
        return 0;
    } else {
        return unparsed_len;
    }
}

static uint16_t get_frame_len_parser(protocol_frame_parser_t *parser)
{
    uint8_t len_1, len_2;
    ring_buffer_peek(parser->ring_buffer, &len_1, FRAME_INDEX_LEN + 0);
    ring_buffer_peek(parser->ring_buffer, &len_2, FRAME_INDEX_LEN + 1);
    return (len_1 << 0) | (len_2 << 8);
}

static uint16_t get_frame_checksum_parser(protocol_frame_parser_t *parser)
{
    uint8_t checksum;
    ring_buffer_peek(parser->ring_buffer, &checksum, parser->next_frame_len - PROTOCOL_FRAME_CHECKSUM_SIZE);
    return checksum;
}

static void get_frame_full_data_parser(protocol_frame_parser_t *parser, uint8_t *data_dest)
{
    ring_buffer_dequeue_arr(parser->ring_buffer, data_dest, parser->next_frame_len);
}

static uint8_t calculate_checksum_parser(protocol_frame_parser_t *parser)
{
    uint32_t i       = 0;
    uint8_t tmp_data = 0;
    uint8_t checksum = 0;
    for (i = 0; i < parser->next_frame_len - PROTOCOL_FRAME_CHECKSUM_SIZE; i++) {
        ring_buffer_peek(parser->ring_buffer, &tmp_data, i);
        checksum += tmp_data;
    }
    return checksum;
}
