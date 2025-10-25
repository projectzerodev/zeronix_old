#pragma once
#include "limine.h"
#include <stddef.h>
#include <stdint.h>

#define PAGE_SIZE 0x1000

void pmm_init(volatile struct limine_memmap_request *memmap_request,
              volatile struct limine_hhdm_request *hhdm_request);
void *palloc(size_t n, bool higher_half);
void pfree(void *addr, size_t n);
