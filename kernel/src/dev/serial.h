#pragma once
#include <stddef.h>

// I couldn't really decide whenether I wanted to name it `serial` or `com`. (serial it is rn)

/**
 * @brief Initializes the serial controller.
 *
 * Initializes the UART16550. I should probably rewrite this to be more DI-ish (IDK xD).
 *
 * I have no idea why this never gets called. Better never call it then :sob:
 */
void _serial_init();

/**
 * @brief Writes a buffer to the serial output
 *
 * @param buf Pointer to the buffer to write.
 * @param len The length of the buffer.
 */
void _serial_write(const char *buf, size_t len);
