#pragma once
#include "arch/amd64/isr/isr.h"

void panic(interrupt_frame_t *registers);
