#pragma once
#include <stddef.h>

// I couldn't really decide whenether I wanted to name it `serial` or `com`. (serial it is rn)

void _serial_init();
void _serial_write(const char *buf, size_t len);
