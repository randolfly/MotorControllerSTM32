#include "Motion/motor.h"
#include "gpio_bsp.h"

void init_motor(motor_t *motor)
{
    motor->motor_config               = (motor_config_t *)malloc(sizeof(motor_config_t));
    motor->motor_config->motion_limit = (motion_limit_t *)malloc(sizeof(motion_limit_t));

    motor->encoder = (encoder_t *)malloc(sizeof(encoder_t));
    init_encoder(motor->encoder);

    motor->motor_param = (motor_param_t *)malloc(sizeof(motor_param_t));
    memset(motor->motor_param, 0, sizeof(motor_param_t));
}

void deinit_motor(motor_t *motor)
{
    free(motor->motor_config->motion_limit);
    free(motor->motor_config);
    deinit_encoder(motor->encoder);
    free(motor->encoder);
    free(motor->motor_param);
}

void enable_motor_electric_power()
{
    set_switch_ch1_on();
}

void disable_motor_electric_power()
{
    set_switch_ch1_off();
}
