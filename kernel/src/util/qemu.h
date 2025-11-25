#pragma once
#include <stdint.h>

#define QEMU_EXIT_SUCCESS 0x10
#define QEMU_EXIT_FAILURE 0x11

/**
 * @brief Exits QEMU.
 *
 * @param code The error code. Use the above.
 */
void qemu_exit(uint8_t code);
