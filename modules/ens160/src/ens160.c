#include "ens160.h"
#include "i2c_lowlevel.h"   // 你之前写的 I2C 基础函数

static uint8_t ens160_addr = ENS160_I2C_ADDR;

bool ens160_init(uint8_t i2c_addr)
{
    ens160_addr = i2c_addr;

    // 读芯片 ID
    uint8_t id[2];
    if (!i2c1_read_regs(ens160_addr, ENS160_REG_PART_ID, id, 2))
        return false;

    // 检查 ID 是否正确 (datasheet: 0x160 = 352)
    uint16_t part_id = (id[1] << 8) | id[0];
    if (part_id != 0x0160)
        return false;

    // 设置标准工作模式
    uint8_t opmode = ENS160_OPMODE_STD;
    if (!i2c1_write_reg(ens160_addr, ENS160_REG_OPMODE, &opmode, 1))
        return false;

    return true;
}

bool ens160_read_aqi(uint16_t *aqi)
{
    uint8_t buf[2];
    if (!i2c1_read_regs(ens160_addr, ENS160_REG_DATA_AQI, buf, 2))
        return false;
    *aqi = (buf[1] << 8) | buf[0];
    return true;
}

bool ens160_read_tvoc(uint16_t *tvoc)
{
    uint8_t buf[2];
    if (!i2c1_read_regs(ens160_addr, ENS160_REG_DATA_TVOC, buf, 2))
        return false;
    *tvoc = (buf[1] << 8) | buf[0];
    return true;
}

bool ens160_read_eco2(uint16_t *eco2)
{
    uint8_t buf[2];
    if (!i2c1_read_regs(ens160_addr, ENS160_REG_DATA_ECO2, buf, 2))
        return false;
    *eco2 = (buf[1] << 8) | buf[0];
    return true;
}
