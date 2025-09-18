#pragma once
#include <__stdarg_va_list.h>

int kprintf(const char *format, ...);
int kvprintf(const char *format, va_list args);
