#pragma once
#include <limine.h>
#include <stddef.h>

int _term_init(struct limine_framebuffer *fb);
void _term_write(const char *buf, size_t len);
