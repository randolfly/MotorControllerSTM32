#include "Motion/encoder.h"

encoder_t encoder               = {0};
encoder_config_t encoder_config = {0};

void encoder_init(encoder_t *encoder, encoder_config_t *encoder_config)
{
    encoder->encoder_config = encoder_config;
}

void encoder_update(encoder_t *encoder, uint32_t encoder_counter)
{
    encoder->current_revolute_counter = encoder_counter;
}