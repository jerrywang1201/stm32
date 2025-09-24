#include "i2c_lowlevel.h"
#include <stdint.h>

/* 寄存器定义（简化版） */
typedef struct {
  volatile uint32_t MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR, BSRR, LCKR, AFR[2];
} GPIO_TypeDef;
typedef struct {
  volatile uint32_t CR1, CR2, OAR1, OAR2, DR, SR1, SR2, CCR, TRISE, FLTR;
} I2C_TypeDef;

#define PERIPH_BASE      0x40000000UL
#define AHB1PERIPH_BASE  (PERIPH_BASE + 0x00020000UL)
#define APB1PERIPH_BASE  (PERIPH_BASE + 0x00000000UL)

#define GPIOB_BASE       (AHB1PERIPH_BASE + 0x0400UL)
#define GPIOB            ((GPIO_TypeDef*)GPIOB_BASE)

#define I2C1_BASE        (APB1PERIPH_BASE + 0x5400UL)
#define I2C1             ((I2C_TypeDef*)I2C1_BASE)

#define RCC_BASE         0x40023800UL
#define RCC_AHB1ENR      (*(volatile uint32_t*)(RCC_BASE + 0x30))
#define RCC_APB1ENR      (*(volatile uint32_t*)(RCC_BASE + 0x40))
#define RCC_GPIOBEN      (1u << 1)
#define RCC_I2C1EN       (1u << 21)

static inline void delay(volatile uint32_t n){ while(n--) __asm volatile("nop"); }

/* I2C 引脚初始化 PB8/PB9 */
void i2c1_pins_init(void) {
  RCC_AHB1ENR |= RCC_GPIOBEN;
  GPIOB->MODER &= ~((3u<<(8*2)) | (3u<<(9*2)));
  GPIOB->MODER |=  ((2u<<(8*2)) | (2u<<(9*2)));    // AF
  GPIOB->OTYPER |=  (1u<<8) | (1u<<9);             // 开漏
  GPIOB->PUPDR &= ~((3u<<(8*2)) | (3u<<(9*2)));
  GPIOB->PUPDR |=  ((1u<<(8*2)) | (1u<<(9*2)));    // 上拉
  GPIOB->AFR[1] &= ~((0xFu<<0) | (0xFu<<4));       // 清 PB8/PB9 AFR
  GPIOB->AFR[1] |=  ((4u<<0) | (4u<<4));           // AF4
}

/* I2C 初始化 */
void i2c1_init(void) {
  RCC_APB1ENR |= RCC_I2C1EN;
  I2C1->CR1 = 0;
  I2C1->CR2 = 16;
  I2C1->CCR = 80;      // 100kHz
  I2C1->TRISE = 17;
  I2C1->CR1 = (1u<<0); // PE
}

/* 写寄存器 */
bool i2c1_write_reg(uint8_t addr7, uint8_t reg, const uint8_t *data, uint32_t n) {
  // TODO: 这里填上你之前 main.c 里的写函数内容
  return true;
}

/* 读寄存器 */
bool i2c1_read_regs(uint8_t addr7, uint8_t reg, uint8_t *data, uint32_t n) {
  // TODO: 这里填上你之前 main.c 里的读函数内容
  return true;
}
