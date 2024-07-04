#include "spi_bsp.h"

/* ========= STATIC FUNCTIONS ================= */

/**
 * @brief write the value to dac register
 * @param  command
 * @param  channel
 * @param  data
 */
static void set_dac_register(uint8_t command, uint16_t channel, uint16_t data);

/**
 * @brief do nothing... floating like universe
 */
static void delay(void);

/* ========= INTERFACE FUNCTIONS ================= */

void init_dac(void)
{
    reset_dac();
}

void set_dac_value(uint16_t channel, uint16_t data)
{
    set_dac_register(CMD_WRITE_UPDATEn, channel, data);
}

void reset_dac(void)
{
    set_dac_register(CMD_RESET, DAC_ALL, 0);
}

/* ========= STATIC FUNCTIONS ================= */

static void set_dac_register(uint8_t command, uint16_t channel, uint16_t data)
{
    uint8_t reg[3] = {0};

    reg[0] = (command << 4) | channel;
    reg[1] = (data >> 8) & 0xFF;
    reg[2] = data & 0xFF;

    SYNC_L;
    delay();
    HAL_SPI_Transmit(&DAC_SPI, reg, 3, 0xF);
    delay();
    SYNC_L;
}

static void delay(void)
{
    uint16_t i;
    for (i = 0; i < 50; i++) {
        __NOP();
    }
}