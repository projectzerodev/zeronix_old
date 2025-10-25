#pragma once
#include "boot/boot.h"

#define HHDM_OFFSET hhdm_request.response->offset

#define HIGHER_HALF(addr)                                                                          \
    ((void *)((uint64_t)(addr) < HHDM_OFFSET ? (uint64_t)(addr) + HHDM_OFFSET : (uint64_t)(addr)))
#define PHYSICAL(addr)                                                                             \
    ((void *)((uint64_t)(addr) >= HHDM_OFFSET ? (uint64_t)(addr) - HHDM_OFFSET : (uint64_t)(addr)))
