#ifndef ENS160_H
#define ENS160_H

#include <stdint.h>
#include <stdbool.h>

// ENS160 默认 I2C 地址 (7-bit)，请用 I2C 扫描确认
#define ENS160_I2C_ADDR       0x53

// 常用寄存器
#define ENS160_REG_PART_ID    0x00
#define ENS160_REG_OPMODE     0x10
#define ENS160_REG_DATA_AQI   0x22
#define ENS160_REG_DATA_TVOC  0x24
#define ENS160_REG_DATA_ECO2  0x22

// OPMODE
#define ENS160_OPMODE_IDLE    0x00
#define ENS160_OPMODE_STD     0x02

// API
bool ens160_init(uint8_t i2c_addr);
bool ens160_read_aqi(uint16_t *aqi);
bool ens160_read_tvoc(uint16_t *tvoc);
bool ens160_read_eco2(uint16_t *eco2);

#endif
