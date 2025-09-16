#include "stdio.h"
#include "../graphics/terminal.h"
#include <printf.h>

void _putchar(char character) {
    _term_write(&character, sizeof(char));
}

void kprintf(const char *format, ...) {
    va_list args;
    va_start(args);
    printf_(format, args);
    va_end(args);
}
