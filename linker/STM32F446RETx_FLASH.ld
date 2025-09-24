/* STM32F446RETx FLASH/RAM */
MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
  RAM   (xrw) : ORIGIN = 0x20000000, LENGTH = 128K
}

/* 供 C 代码引用的符号 */
_estack   = ORIGIN(RAM) + LENGTH(RAM); /* 顶部作为初始栈指针 */
_Min_Heap_Size = 0x000; /* 如需 malloc 可调大 */
_Min_Stack_Size = 0x800;

ENTRY(Reset_Handler)

SECTIONS
{
  /* 向量表与代码放在 FLASH */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } > FLASH

  .text :
  {
    . = ALIGN(4);
    *(.text*)
    *(.rodata*)
    . = ALIGN(4);

    /* 异常表必须在 .text/rodata 后，位于 FLASH，且在 .data 的 LMA 之前 */
    /* extab/exidx 顺序要在 _etext 之前 */
    KEEP(*(.ARM.extab* .gnu.linkonce.armextab.*))
    . = ALIGN(4);
    __exidx_start = .;
    KEEP(*(.ARM.exidx* .gnu.linkonce.armexidx.*))
    __exidx_end = .;
    . = ALIGN(4);
  } > FLASH

  /* 用于计算 .data 的 LMA 起点 */
  _etext = .;

  /* 初始化数据段，VMA 在 RAM，LMA 在 FLASH，拷贝源地址给 _sidata */
  .data : AT ( _etext )
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } > RAM
  _sidata = LOADADDR(.data);

  /* BSS */
  .bss (NOLOAD) :
  {
    . = ALIGN(4);
    _sbss = .;
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } > RAM

  /* 堆和栈，仅用于符号定位，不实际分配物理空间 */
  ._user_heap_stack (NOLOAD):
  {
    . = ALIGN(8);
    PROVIDE(_end = .);
    PROVIDE(end  = _end);
  } > RAM

  /* 断言：检查镜像是否溢出 FLASH/RAM */
  ASSERT( (_etext + SIZEOF(.data)) <= (ORIGIN(FLASH) + LENGTH(FLASH)), "FLASH overflow")
  ASSERT( (_ebss + _Min_Stack_Size) <= (ORIGIN(RAM) + LENGTH(RAM)), "RAM overflow")
}
