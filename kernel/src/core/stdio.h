#pragma once
#include <__stdarg_va_list.h>

void _stdio_init();

int kprintf(const char *format, ...);
int kvprintf(const char *format, va_list args);
