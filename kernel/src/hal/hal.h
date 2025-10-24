#pragma once
#include <stdint.h>

extern uint64_t kvirt;
extern uint64_t kphys;

void hal_early_init();
void hal_base_init();
