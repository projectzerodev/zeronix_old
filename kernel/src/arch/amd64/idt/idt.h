#pragma once
#include <stdint.h>

#define IDT_MAX_DESCRIPTORS 256

void amd64_idt_init();
void amd64_idt_set_gate(uint8_t index, void *base, uint16_t selector, uint8_t flags);
