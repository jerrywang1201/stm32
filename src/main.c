#include <stdint.h>

/* -------- GPIO 寄存器结构 -------- */
typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} GPIO_TypeDef;

/* -------- 基地址 -------- */
#define PERIPH_BASE      (0x40000000UL)
#define AHB1PERIPH_BASE  (PERIPH_BASE + 0x00020000UL)
#define RCC_BASE         (0x40023800UL)

#define GPIOA_BASE       (AHB1PERIPH_BASE + 0x0000UL)
#define GPIOC_BASE       (AHB1PERIPH_BASE + 0x0800UL)

#define GPIOA            ((GPIO_TypeDef*)GPIOA_BASE)
#define GPIOC            ((GPIO_TypeDef*)GPIOC_BASE)

#define RCC_AHB1ENR      (*(volatile uint32_t*)(RCC_BASE + 0x30UL))
#define RCC_GPIOAEN      (1u << 0)
#define RCC_GPIOCEN      (1u << 2)

/* -------- SysTick 寄存器 -------- */
typedef struct {
    volatile uint32_t CTRL;
    volatile uint32_t LOAD;
    volatile uint32_t VAL;
    volatile uint32_t CALIB;
} SYST_Type;

#define SYST        ((SYST_Type*)0xE000E010UL)
#define SYST_CLKSRC (1u << 2)
#define SYST_TICKINT (1u << 1)
#define SYST_ENABLE (1u << 0)

#define F_CPU 16000000u  // 默认 HSI 16MHz

/* -------- LED 定义 -------- */
#define LED_PORT   GPIOA      // Nucleo-F446RE 板载 LD2 = PA5
#define LED_PIN    5u
#define LED_CLKEN  RCC_GPIOAEN

/* -------- 全局变量 -------- */
volatile uint32_t g_ms = 0;

/* -------- 初始化 GPIO -------- */
static void gpio_init_output(GPIO_TypeDef* port, uint32_t pin, uint32_t clk)
{
    RCC_AHB1ENR |= clk;
    port->MODER &= ~(0x3u << (pin * 2));
    port->MODER |=  (0x1u << (pin * 2));
    port->OTYPER &= ~(1u << pin);
    port->OSPEEDR &= ~(0x3u << (pin * 2));
    port->PUPDR &= ~(0x3u << (pin * 2));
}

/* -------- LED 操作 -------- */
static inline void led_on(void)  { LED_PORT->BSRR = (1u << LED_PIN); }
static inline void led_off(void) { LED_PORT->BSRR = (1u << (LED_PIN + 16)); }
static inline void led_toggle(void)
{
    if (LED_PORT->ODR & (1u << LED_PIN)) led_off(); else led_on();
}

/* -------- SysTick Handler -------- */
void SysTick_Handler(void)
{
    g_ms++;   // 每 1ms 中断一次
}

/* -------- 主函数 -------- */
int main(void)
{
    gpio_init_output(LED_PORT, LED_PIN, LED_CLKEN);

    // SysTick 配置为 1ms 节拍
    SYST->LOAD  = (F_CPU / 1000u) - 1u; // 16000 - 1
    SYST->VAL   = 0;
    SYST->CTRL  = SYST_CLKSRC | SYST_TICKINT | SYST_ENABLE;

    uint32_t last = 0;

    while (1) {
        if ((g_ms - last) >= 500u) {   // 每 500ms 翻转一次
            last = g_ms;
            led_toggle();
        }
    }
}
