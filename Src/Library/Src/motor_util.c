#include "motor_util.h"

uint32_t torque_permillage_to_dac(float torque_permillage)
{
    return (uint32_t)(torque_permillage * 4096.0 / 2000.0 + 2048.0);
}