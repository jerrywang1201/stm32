/* Minimal startup for STM32F446xx (Cortex-M4F) */
.syntax unified
.cpu cortex-m4
.fpu fpv4-sp-d16
.thumb

.global g_pfnVectors
.global Reset_Handler

/* 128 KB RAM: 0x20000000 + 0x20000 = 0x20020000 */
.equ  _estack, 0x20020000

.section .isr_vector,"a",%progbits
.type g_pfnVectors, %object
g_pfnVectors:
  .word _estack
  .word Reset_Handler
  .word NMI_Handler
  .word HardFault_Handler
  .word MemManage_Handler
  .word BusFault_Handler
  .word UsageFault_Handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word SVC_Handler
  .word DebugMon_Handler
  .word 0
  .word PendSV_Handler
  .word SysTick_Handler
  .rept 82
  .word Default_Handler
  .endr
.size g_pfnVectors, . - g_pfnVectors

.text
.thumb
.align 2
.type Reset_Handler, %function
Reset_Handler:
  bl  SystemInit
  bl  main
.Lhang:
  b   .Lhang
.size Reset_Handler, . - Reset_Handler

.weak NMI_Handler
.weak HardFault_Handler
.weak MemManage_Handler
.weak BusFault_Handler
.weak UsageFault_Handler
.weak SVC_Handler
.weak DebugMon_Handler
.weak PendSV_Handler
.weak SysTick_Handler

.type Default_Handler, %function
Default_Handler:
  b   Default_Handler
.size Default_Handler, . - Default_Handler

NMI_Handler:          b Default_Handler
HardFault_Handler:    b Default_Handler
MemManage_Handler:    b Default_Handler
BusFault_Handler:     b Default_Handler
UsageFault_Handler:   b Default_Handler
SVC_Handler:          b Default_Handler
DebugMon_Handler:     b Default_Handler
PendSV_Handler:       b Default_Handler
SysTick_Handler:      b Default_Handler
