#pragma once
#include <limine.h>
#include <stddef.h>
#include <stdint.h>

typedef struct
{
    size_t columns;
    size_t rows;
} terminal_dimensions_t;

terminal_dimensions_t _term_init(struct limine_framebuffer *fb);
void _term_write(const char *buf, size_t len);
