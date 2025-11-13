#pragma once

#include <stdint.h>

void ps2_keyboard_init();
void keyboard_irq_handler(void *ctx);
void ps2_keyboard_getchar(uint8_t scancode);