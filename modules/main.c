#include <stdio.h>
#include <stdint.h>
#include "uart2.h"
#include "i2c_lowlevel.h"
#include "ens160.h"

extern void SystemInit(void);

int main(void) {
    SystemInit();
    uart2_init();
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("\r\nBOOT: UART2@115200 HSI16MHz\r\n");

    i2c1_pins_init();
    i2c1_init();
    if (!ens160_init(ENS160_I2C_ADDR)) { while (1) {} }

    printf("ENS160 demo start\r\n");

    uint16_t aqi, tvoc, eco2;
    while (1) {
        if (ens160_read_aqi(&aqi))  { printf("AQI=%u\r\n", aqi); }
        if (ens160_read_tvoc(&tvoc)) { printf("TVOC=%u ppb\r\n", tvoc); }
        if (ens160_read_eco2(&eco2)) { printf("eCO2=%u ppm\r\n", eco2); }
        for (volatile uint32_t i = 0; i < 1000000; i++) {}
    }
}
