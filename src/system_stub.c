// src/system_stub.c
#include <stdint.h>

uint32_t SystemCoreClock = 16000000U;  // 可选：给个默认时钟值

static inline void enable_fpu(void) {
  volatile uint32_t *CPACR = (uint32_t *)0xE000ED88; // SCB->CPACR
  *CPACR |= (0xFu << 20); // full access to CP10/CP11
}

void SystemInit(void) {
  enable_fpu();
  // 这里以后可以加时钟/HSE/PLL初始化；现在留空也能跑
}
