#include "stdio.h"
#include "../graphics/terminal.h"
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

void _putchar(char character) {
    _term_write(&character, sizeof(char));
}

int kprintf(const char *format, ...) {
    (void)format;
    char buffer[1024];
    va_list args;

    va_start(args);
    int length = npf_vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    if (length < 0 || length >= (int)sizeof(buffer)) {
        return -1;
    }

    _term_write(buffer, length);

    return length;
}
