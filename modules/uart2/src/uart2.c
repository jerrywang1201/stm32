#include "uart2.h"
#include <stdint.h>
#define PERIPH_BASE 0x40000000UL
#define AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000UL)
#define APB1PERIPH_BASE (PERIPH_BASE + 0x00000000UL)
#define RCC_BASE (AHB1PERIPH_BASE + 0x3800UL)
#define GPIOA_BASE (AHB1PERIPH_BASE + 0x0000UL)
#define USART2_BASE (APB1PERIPH_BASE + 0x4400UL)
#define RCC_AHB1ENR (*(volatile uint32_t*)(RCC_BASE + 0x30))
#define RCC_APB1ENR (*(volatile uint32_t*)(RCC_BASE + 0x40))
#define GPIOA_MODER (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOA_AFRL  (*(volatile uint32_t*)(GPIOA_BASE + 0x20))
#define GPIOA_PUPDR (*(volatile uint32_t*)(GPIOA_BASE + 0x0C))
#define USART2_SR   (*(volatile uint32_t*)(USART2_BASE + 0x00))
#define USART2_DR   (*(volatile uint32_t*)(USART2_BASE + 0x04))
#define USART2_BRR  (*(volatile uint32_t*)(USART2_BASE + 0x08))
#define USART2_CR1  (*(volatile uint32_t*)(USART2_BASE + 0x0C))
void uart2_init(void){
    RCC_AHB1ENR |= (1u<<0);
    RCC_APB1ENR |= (1u<<17);
    GPIOA_MODER &= ~((3u<<(2*2))|(3u<<(3*2)));
    GPIOA_MODER |=  ((2u<<(2*2))|(2u<<(3*2)));
    GPIOA_AFRL  &= ~((0xFu<<(4*2))|(0xFu<<(4*3)));
    GPIOA_AFRL  |=  ((7u<<(4*2))|(7u<<(4*3)));
    GPIOA_PUPDR &= ~((3u<<(2*2))|(3u<<(3*2)));
    GPIOA_PUPDR |=  ((1u<<(2*2))|(1u<<(3*2)));
    USART2_CR1 = 0;
    USART2_BRR = (uint16_t)((16000000UL + 115200/2)/115200);
    USART2_CR1 |= (1u<<13)|(1u<<3)|(1u<<2);
}
void uart2_write_byte(uint8_t b){
    while(((USART2_SR>>7)&1u)==0){}
    USART2_DR = b;
}
void uart2_write(const void* buf, uint32_t len){
    const uint8_t* p = (const uint8_t*)buf;
    for(uint32_t i=0;i<len;i++) uart2_write_byte(p[i]);
}
