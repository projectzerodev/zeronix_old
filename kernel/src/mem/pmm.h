#pragma once
#include "limine.h"
#include <stddef.h>
#include <stdint.h>

#define PAGE_SIZE 0x1000

typedef uint64_t physaddr_t;

void pmm_init(volatile struct limine_memmap_request *memmap_request,
              volatile struct limine_hhdm_request *hhdm_request);
physaddr_t palloc(size_t n);
void pfree(physaddr_t addr, size_t n);
