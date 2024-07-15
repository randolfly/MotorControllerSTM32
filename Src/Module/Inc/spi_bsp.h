/**
 * @file spi_bsp.h
 * @brief this is the bsp file for spi, which provides the dac control functions(the dac device is communicated by spi)
 * @author randolf (1665718426@qq.com)
 * @version 1.0.1
 * @date 2024-07-15
 *
 * @copyright Copyright (c) 2024  randolf
 *
 */
#ifndef __SPI_BSP_H__
#define __SPI_BSP_H__

#include "Util/type_def_protocol.h"
#include "spi.h"

#ifdef STM32H743xx
#include "main.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define DAC_SPI           hspi2

#define CMD_WRITE_UPDATEn 3
#define CMD_RESET         6

#define DAC_A             0x01
#define DAC_B             0x08
#define DAC_ALL           0x09

#define SCLK_H            HAL_GPIO_WritePin(DAC_SPI_SCLK_GPIO_Port, DAC_SPI_SCLK_Pin, GPIO_PIN_SET)
#define SCLK_L            HAL_GPIO_WritePin(DAC_SPI_SCLK_GPIO_Port, DAC_SPI_SCLK_Pin, GPIO_PIN_RESET)
#define SYC_H             HAL_GPIO_WritePin(DAC_SPI_SCLK_GPIO_Port, DAC_SPI_SCLK_Pin, GPIO_PIN_SET)
#define SYC_L             HAL_GPIO_WritePin(DAC_SPI_SCLK_GPIO_Port, DAC_SPI_SCLK_Pin, GPIO_PIN_RESET)
#define SYNC_H            HAL_GPIO_WritePin(DAC_SPI_SYNC_GPIO_Port, DAC_SPI_SYNC_Pin, GPIO_PIN_SET)
#define SYNC_L            HAL_GPIO_WritePin(DAC_SPI_SYNC_GPIO_Port, DAC_SPI_SYNC_Pin, GPIO_PIN_RESET)

/**
 * @brief initialize dac device
 */
void init_dac(void);

/**
 * @brief set the dac output data
 * @param  channel: dac output channel
 * @param  data: value range: [0x0000, 0xFFFF]
 */
void set_dac_value(uint16_t channel, uint16_t data);

/**
 * @brief software reset dac value
 */
void reset_dac(void);

#ifdef _cplusplus
}
#endif
#endif