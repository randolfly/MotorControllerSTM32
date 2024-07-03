#include "Motion/motor.h"

void init_motor(motor_t *motor)
{
    motor->motor_config               = (motor_config_t *)malloc(sizeof(motor_config_t));
    motor->motor_config->motion_limit = (motion_limit_t *)malloc(sizeof(motion_limit_t));

    motor->encoder = (encoder_t *)malloc(sizeof(encoder_t));
    init_encoder(motor->encoder);
}

void deinit_motor(motor_t *motor)
{
    free(motor->motor_config->motion_limit);
    free(motor->motor_config);
    deinit_encoder(motor->encoder);
    free(motor->encoder);
}