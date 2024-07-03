#include "Motion/encoder.h"

encoder_t encoder               = {0};
encoder_config_t encoder_config = {0};

void init_encoder(encoder_t *encoder)
{
    encoder->encoder_config                 = (encoder_config_t *)malloc(sizeof(encoder_config_t));
    encoder->encoder_config->start_position = 0;
    encoder->velocity_diff_model            = (encoder_velocity_diff_t *)malloc(sizeof(encoder_velocity_diff_t));
    init_encoder_velocity_diff(encoder->velocity_diff_model);
}

void deinit_encoder(encoder_t *encoder)
{
    free(encoder->encoder_config);
    deinit_encoder_velocity_diff(encoder->velocity_diff_model);
    free(encoder->velocity_diff_model);
}

void encoder_update(encoder_t *encoder, uint32_t encoder_counter)
{
    encoder->current_revolute_counter = encoder_counter;

    encoder->position = encoder->encoder_config->start_position + ((double)(encoder->current_revolute_counter) / ENCODER_RESOLUTION + encoder->rotation_num) * 2 * PI;
}
