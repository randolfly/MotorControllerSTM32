/**
 * @file gpio_bsp.h
 * @brief this is the bsp file for gpio, which provides the switch control functions
 * @author randolf (1665718426@qq.com)
 * @version 1.0.1
 * @date 2024-07-15
 *
 * @copyright Copyright (c) 2024  randolf
 *
 */
#ifndef __GPIO_BSP_H__
#define __GPIO_BSP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "gpio.h"
#include "tim_bsp.h"

/**
 * @brief Set the switch ch1 on->24V on
 */
void set_switch_ch1_on(void);

/**
 * @brief Set the switch ch1 off->24V off
 */
void set_switch_ch1_off(void);

/**
 * @brief Set the switch ch2 on->24V on
 */
void set_switch_ch2_on(void);

/**
 * @brief Set the switch ch2 off->24V off
 */
void set_switch_ch2_off(void);

#ifdef __cplusplus
}
#endif

#endif // __GPIO_BSP_H__