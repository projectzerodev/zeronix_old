#pragma once
#include <__stdarg_va_list.h>

/**
 * @brief Initializes `kprintf`
 */
void _kprintf_init();

/**
 * @brief Prints the specified format to the term and serial devices.
 *
 * @param fmt The format to print.
 * @param ... Other stuff (idk what it is called)
 * @return Length of printed buffer (max 1024 bytes) (-1 on fail)
 */
int kprintf(const char *fmt, ...);
int kvprintf(const char *fmt, va_list args);
