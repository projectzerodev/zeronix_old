#pragma once
#include "arch/amd64/isr/isr.h"

#define panic(x, ...)                                                                              \
    _Generic((x),                                                                                  \
        const char *: panic_message,                                                               \
        char *: panic_message,                                                                     \
        amd64_interrupt_frame_t *: panic_interrupt)(x, ##__VA_ARGS__)

void panic_message(const char *msg, ...);
void panic_interrupt(amd64_interrupt_frame_t *frame);
