#ifndef __MAIN_APP_H__
#define __MAIN_APP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdio.h>
#include "spi_bsp.h"
#include "gpio_bsp.h"
#include "tim_bsp.h"
#include "usart_bsp.h"

#include "Util/task_scheduler.h"
#include "Util/type_def_protocol.h"
#include "Util/string_operator.h"
#include "Util/dictionary.h"
#include "Motion/motor.h"
#include "Controller/motion_statemachine.h"
#include "Controller/model_excitation.h"
#include "Controller/velocity_controller.h"

/**
 * @brief init the bsp layer provided app functions
 */
void Init_App_Functions(void);

/**
 * @brief run the main app functions
 */
void Run_App_Functions(void);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_APP_H__