#pragma once
#include <stdint.h>

void amd64_pit_init();
uint64_t amd64_pit_get_ticks();
void amd64_pit_set_ticks(uint64_t t);
