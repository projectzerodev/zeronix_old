#pragma once
#include "arch/amd64/isr/isr.h"

/**
 * @brief Generic for panicking.
 */
#define panic(x, ...)                                                                              \
    _Generic((x),                                                                                  \
        const char *: panic_message,                                                               \
        char *: panic_message,                                                                     \
        amd64_interrupt_frame_t *: panic_interrupt)(x, ##__VA_ARGS__)

/**
 * @brief Panic and and output a message.
 *
 * @param msg The format of the message to output.
 * @param ... Other stuff...
 */
void panic_message(const char *msg, ...);

/**
 * @brief Panic and output an IST.
 *
 * @param frame The IST to output.
 */
void panic_interrupt(amd64_interrupt_frame_t *frame);
