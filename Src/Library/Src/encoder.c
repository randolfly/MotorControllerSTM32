#include "encoder.h"

Encoder encoder              = {0};
EncoderConfig encoder_config = {0};

void encoder_init(Encoder *encoder, EncoderConfig *encoder_config)
{
    encoder->encoder_config = encoder_config;
}

void encoder_update(Encoder *encoder, uint32_t encoder_counter)
{
    encoder->current_revolute_counter = encoder_counter;
}