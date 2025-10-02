#include "stdio.h"
#include "../graphics/terminal.h"
#include "devices/uart16550/uart.h"
#include <stdarg.h>

#define NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS     1
#define NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS       1
#define NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS           0
#define NANOPRINTF_USE_SMALL_FORMAT_SPECIFIERS           1
#define NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS           1
#define NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS          1
#define NANOPRINTF_USE_WRITEBACK_FORMAT_SPECIFIERS       0
#define NANOPRINTF_SNPRINTF_SAFE_TRIM_STRING_ON_OVERFLOW 1

#define NANOPRINTF_IMPLEMENTATION
#include <nanoprintf.h>

int kprintf(const char *format, ...)
{
    char buffer[1024];
    va_list args;

    va_start(args, format);
    int length = npf_vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    if (length < 0 || length >= (int)sizeof(buffer))
    {
        return -1;
    }

    _uart_write(buffer, length);
    _term_write(buffer, length);

    return length;
}

int kvprintf(const char *format, va_list args)
{
    char buffer[1024];

    int length = npf_vsnprintf(buffer, sizeof(buffer), format, args);

    if (length < 0 || length >= (int)sizeof(buffer))
    {
        return -1;
    }

    _uart_write(buffer, length);
    _term_write(buffer, length);

    return length;
}
