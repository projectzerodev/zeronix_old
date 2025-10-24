#pragma once
#include <limine.h>
#include <stdint.h>

#define PAGE_SIZE    0x1000
#define PAGE_PRESENT (1ULL << 0)
#define PAGE_WRITE   (1ULL << 1)
#define PAGE_USER    (1ULL << 2)
#define PAGE_NX      (1ULL << 63)

int amd64_paging_map(uint64_t *pagemap, uint64_t virt, uint64_t phys, uint64_t flags);
void amd64_paging_init(volatile struct limine_memmap_request *memmap_request);
