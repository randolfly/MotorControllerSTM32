#include "Controller/motion_statemachine.h"

void init_motion_state_machine(motion_state_machine_t *motion_state_machine)
{
    motion_state_machine->state                 = MOTION_INIT;
    motion_state_machine->event.idle_to_exit    = 0;
    motion_state_machine->event.idle_to_pos     = 0;
    motion_state_machine->event.idle_to_torque  = 0;
    motion_state_machine->event.idle_to_vel     = 0;
    motion_state_machine->event.init_to_poweron = 0;
    motion_state_machine->event.pos_to_idle     = 0;
    motion_state_machine->event.torque_to_idle  = 0;
    motion_state_machine->event.vel_to_idle     = 0;
}

void update_motion_state_machine(motion_state_machine_t *motion_state_machine)
{
    switch (motion_state_machine->state) {
        case MOTION_INIT:
            // init motion state(maybe init controller)
            if (motion_state_machine->event.init_to_poweron == 1) {
                motion_state_machine->state = MOTION_POWERON;
#ifdef DEBUG
                printf("INIT to POWERON state\n");
#endif // DEBUG
            }
            break;
        case MOTION_POWERON:
            break;
        default:
            break;
    }
}