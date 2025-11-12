#pragma once
#include "limine.h"
#include <stdint.h>

// PMLE Flags
// from
// https://github.com/tyler-ottman/tellurium-os/blob/01cf40ba4ab872e81bc98d6c740174c42b029376/kernel/memory/vmm.h#L15
#define PMLE_PRESENT        1
#define PMLE_WRITE          (1 << 1)
#define PMLE_USER           (1 << 2)
#define PMLE_PWT            (1 << 3)
#define PMLE_PCD            (1 << 4)
#define PMLE_ACCESSED       (1 << 5)
#define PMLE_NOT_EXECUTABLE (1ull << 63)

#define PMLT_MASK 0x1ff

#define PML4_INDEX(a) ((a >> 39) & PMLT_MASK)
#define PML3_INDEX(a) ((a >> 30) & PMLT_MASK)
#define PML2_INDEX(a) ((a >> 21) & PMLT_MASK)
#define PML1_INDEX(a) ((a >> 12) & PMLT_MASK)

#define PAGE_ADDR_MASK   0xFFFFFFFFFFFFF000ULL
#define PAGE_FLAGS(a)    ((a) & ~(PAGE_ADDR_MASK))
#define PAGE_GET_ADDR(a) ((a) & PAGE_ADDR_MASK)

extern uint64_t get_pml4();

void amd64_paging_init(volatile struct limine_memmap_request *memmap_request);
void amd64_paging_map_region(uint64_t *pml4, uint64_t phys_start, uint64_t virt_start,
                             uint64_t length, uint64_t flags);
