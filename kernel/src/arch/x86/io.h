#pragma once
#include <stdint.h>

uint8_t x86_inb(uint16_t port);
void x86_outb(uint16_t port, uint8_t val);
