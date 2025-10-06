#pragma once
#include <stdint.h>

void pit8253_init();
uint64_t pit8253_get_ticks();
void pit8253_set_ticks(uint64_t t);
