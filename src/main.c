#include <stdint.h>

void SystemInit(void) {}
void SysTick_Handler(void) {}

static void delay(volatile uint32_t t){ while(t--) __asm__("nop"); }

int main(void) {
    // 裸机最小循环（点灯/串口需要相应外设初始化）
    while (1) { delay(1000000); }
}
