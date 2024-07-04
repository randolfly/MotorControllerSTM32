#include "Motion/encoder.h"
#include "tim_bsp.h"

void init_encoder(encoder_t *encoder)
{
    encoder->rotation_num                   = 0;
    encoder->last_counter                   = 0;
    encoder->position                       = 0;
    encoder->velocity                       = 0;
    encoder->acceleration                   = 0;
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
    // check overflow
    int64_t counter_diff = (int64_t)(encoder->last_counter) - (int64_t)(encoder_counter);

    if (counter_diff > ENCODER_RESOLUTION / 4) {
        encoder->rotation_num += 1;
    } else if (counter_diff < (-ENCODER_RESOLUTION / 4)) {
        encoder->rotation_num -= 1;
    }

    encoder->position = encoder->encoder_config->start_position +
                        (((double)(encoder_counter) + 1) / ENCODER_RESOLUTION + encoder->rotation_num) * 2 * PI;

    encoder->last_counter = encoder_counter;
    // set velocity_diff model input
    step_encoder_velocity_diff(encoder->velocity_diff_model,
                               (encoder->position),
                               &(encoder->velocity));
}