/**
 * @file main_app.h
 * @brief assembly the app functions to a united app
 * @author randolf (1665718426@qq.com)
 * @version 1.0.1
 * @date 2024-07-15
 *
 * @copyright Copyright (c) 2024  randolf
 *
 */
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
#include "Controller/position_controller.h"
#include "Controller/s_profile_generator.h"

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