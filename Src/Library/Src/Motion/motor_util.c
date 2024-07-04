#include "Motion/motor_util.h"

uint16_t torque_permillage_to_dac(float torque_permillage)
{
    if (torque_permillage > 1000.0) {
        torque_permillage = 1000.0;
    } else if (torque_permillage < -1000.0) {
        torque_permillage = -1000.0;
    }

    return (uint16_t)(torque_permillage * (float)(0xFFFF) / 2000.0 + (float)(0xFFFF) / 2.0);
}