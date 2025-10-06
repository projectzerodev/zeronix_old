#pragma once
#include <stdint.h>

void pic8259_init();
void pic8259_set_mask(uint16_t new_mask);
void pic8259_send_eoi(int irq);
void pic8259_mask(int irq);
void pic8259_unmask(int irq);
