/* STM32F446RE: 512K FLASH, 128K RAM */
MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
  RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
  .isr_vector :
  {
    KEEP(*(.isr_vector))
  } > FLASH

  .text :
  {
    *(.text*)
    *(.rodata*)
  } > FLASH

  .ARM.exidx :
  {
    *(.ARM.exidx*)
  } > FLASH

  .data : AT (ADDR(.text) + SIZEOF(.text) + SIZEOF(.ARM.exidx))
  {
    *(.data*)
  } > RAM

  .bss :
  {
    *(.bss*)
    *(COMMON)
  } > RAM
}
