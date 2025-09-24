#include <stdint.h>
#define PERIPH_BASE   0x40000000UL
#define AHB1_BASE     (PERIPH_BASE + 0x00020000UL)
#define RCC_BASE      (AHB1_BASE   + 0x3800UL)
#define GPIOA_BASE    (AHB1_BASE   + 0x0000UL)

#define RCC_AHB1ENR   (*(volatile uint32_t*)(RCC_BASE + 0x30))
#define GPIOA_MODER   (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOA_ODR     (*(volatile uint32_t*)(GPIOA_BASE + 0x14))

static void delay(volatile uint32_t t){ while(t--) __asm__("nop"); }

int main(void){
  RCC_AHB1ENR |= (1u<<0);           // enable GPIOA
  GPIOA_MODER &= ~(3u<<(5*2));
  GPIOA_MODER |=  (1u<<(5*2));      // PA5 output
  for(;;){
    GPIOA_ODR ^= (1u<<5);           // toggle LD2
    delay(200000);
  }
}
