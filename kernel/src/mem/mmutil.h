#pragma once
#include "boot/boot.h"

extern uint64_t __kernel_start, __kernel_end;
extern uint64_t __kernel_text_start, __kernel_text_end;
extern uint64_t __kernel_data_start, __kernel_data_end;
extern uint64_t __kernel_rodata_start, __kernel_rodata_end;
extern uint64_t __limine_requests_start, __limine_requests_end;

#define HHDM_OFFSET hhdm_request.response->offset
#define VIRT_BASE   address_request.response->virtual_base
#define PHYS_BASE   address_request.response->physical_base

#define HIGHER_HALF(addr)                                                                          \
    ((void *)((uint64_t)(addr) < HHDM_OFFSET ? (uint64_t)(addr) + HHDM_OFFSET : (uint64_t)(addr)))
#define PHYSICAL(addr)                                                                             \
    ((void *)((uint64_t)(addr) >= HHDM_OFFSET ? (uint64_t)(addr) - HHDM_OFFSET : (uint64_t)(addr)))
