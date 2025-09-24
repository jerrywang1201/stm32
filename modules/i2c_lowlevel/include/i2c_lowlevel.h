#ifndef I2C_LOWLEVEL_H
#define I2C_LOWLEVEL_H

#include <stdint.h>
#include <stdbool.h>

void i2c1_pins_init(void);
void i2c1_init(void);

bool i2c1_write_reg(uint8_t addr7, uint8_t reg, const uint8_t *data, uint32_t n);
bool i2c1_read_regs(uint8_t addr7, uint8_t reg, uint8_t *data, uint32_t n);

#endif
