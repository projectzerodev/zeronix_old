#pragma once
#include <__stdarg_va_list.h>

void _kprintf_init();
int kprintf(const char *fmt, ...);
int kvprintf(const char *fmt, va_list args);
