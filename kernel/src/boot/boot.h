#pragma once
#include <stdint.h>

extern volatile uint64_t limine_base_revision[3];
extern volatile uint64_t limine_requests_start_marker[4];
extern volatile uint64_t limine_requests_end_marker[2];

extern volatile struct limine_framebuffer_request framebuffer_request;
