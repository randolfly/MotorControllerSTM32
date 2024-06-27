#include "Motion/motor_util.h"

uint32_t torque_permillage_to_dac(float torque_permillage)
{
    if (torque_permillage > 1000.0) {
        torque_permillage = 1000.0;
    } else if (torque_permillage < -1000.0) {
        torque_permillage = -1000.0;
    }

    return (uint32_t)(torque_permillage * 4096.0 / 2000.0 + 2048.0);
}