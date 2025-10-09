#pragma once
#include <stddef.h>

/**
 * @brief Sets up the COM1 port.
 */
void _com_init();

/**
 * @brief Writes data to the COM1 port.
 */
void _com_write(const char *buf, size_t len);
