#pragma once
#include <stdint.h>

void amd64_pic_init();
void amd64_pic_set_mask(uint16_t new_mask);
void amd64_pic_send_eoi(int irq);
void amd64_pic_mask(int irq);
void amd64_pic_unmask(int irq);
