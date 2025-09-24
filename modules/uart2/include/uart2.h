#pragma once
#include <stdint.h>
void uart2_init(void);
void uart2_write_byte(uint8_t b);
void uart2_write(const void* buf, uint32_t len);
