#include "paging.h"
#include "core/panic.h"
#include "hal/hal.h"
#include "lib/align.h"
#include "limine.h"
#include "mem/mmutil.h"
#include "mem/pmm.h"
#include "util/log.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

extern uint64_t kernel_stack_top;
extern char __limine_requests_start[];
extern char __limine_requests_end[];
extern char __text_start[];
extern char __text_end[];
extern char __rodata_start[];
extern char __rodata_end[];
extern char __data_start[];
extern char __data_end[];

#define PAGE_FRAME_MASK 0x000FFFFFFFFFF000ULL
#define PML_INDEX_MASK  0x1ffULL
#define PML_SHIFT_L1    12
#define PML_SHIFT_L2    21
#define PML_SHIFT_L3    30
#define PML_SHIFT_L4    39

uint64_t *kernel_pagemap = NULL;

void set_pagemap(uint64_t *pagemap)
{
    if (!pagemap || !IS_PAGE_ALIGNED((uint64_t)PHYSICAL(pagemap)))
    {
        panic("Invalid pagemap, %p", pagemap);
    }
    __asm__ volatile("movq %0, %%cr3" ::"r"((uint64_t)PHYSICAL(pagemap)) : "memory");
}

void amd64_paging_init(volatile struct limine_memmap_request *memmap_request)
{
    struct limine_memmap_response *memmap = memmap_request->response;

    if (kernel_pagemap)
    {
        log_warn("Kernel pagemap is already initialized");
        return;
    }

    kernel_pagemap = palloc(1, false);
    if (!kernel_pagemap)
    {
        panic("Failed to allocate new kernel pagemap");
    }

    memset((void *)HIGHER_HALF(kernel_pagemap), 0, PAGE_SIZE);
    log_debug("Allocated new kernel pagemap at 0x%x", kernel_pagemap);

    uint64_t stack_top = ALIGN_UP(kernel_stack_top, PAGE_SIZE);
    for (uint64_t addr = stack_top - (16 * 1024); addr < stack_top; addr += PAGE_SIZE)
    {
        uint64_t phys = (uint64_t)PHYSICAL(addr);
        amd64_paging_map(kernel_pagemap, addr, phys, PAGE_PRESENT | PAGE_WRITE | PAGE_NX);
    }

    uint64_t requests_start = ALIGN_DOWN(__limine_requests_start, PAGE_SIZE);
    uint64_t requests_end   = ALIGN_UP(__limine_requests_end, PAGE_SIZE);
    for (uint64_t reqs = requests_start; reqs < requests_end; reqs += PAGE_SIZE)
    {
        amd64_paging_map(kernel_pagemap, reqs, reqs - kvirt + kphys, PAGE_PRESENT | PAGE_WRITE);
    }

    uint64_t text_start = ALIGN_DOWN((uint64_t)__text_start, PAGE_SIZE);
    uint64_t text_end   = ALIGN_UP((uint64_t)__text_end, PAGE_SIZE);
    for (uint64_t addr = text_start; addr < text_end; addr += PAGE_SIZE)
    {
        uint64_t phys = addr - kvirt + kphys;
        amd64_paging_map(kernel_pagemap, addr, phys, PAGE_PRESENT);
    }

    uint64_t rodata_start = ALIGN_DOWN((uint64_t)__rodata_start, PAGE_SIZE);
    uint64_t rodata_end   = ALIGN_UP((uint64_t)__rodata_end, PAGE_SIZE);
    for (uint64_t addr = rodata_start; addr < rodata_end; addr += PAGE_SIZE)
    {
        uint64_t phys = addr - kvirt + kphys;
        amd64_paging_map(kernel_pagemap, addr, phys, PAGE_PRESENT | PAGE_NX);
    }

    uint64_t data_start = ALIGN_DOWN((uint64_t)__data_start, PAGE_SIZE);
    uint64_t data_end   = ALIGN_UP((uint64_t)__data_end, PAGE_SIZE);
    for (uint64_t addr = data_start; addr < data_end; addr += PAGE_SIZE)
    {
        uint64_t phys = addr - kvirt + kphys;
        amd64_paging_map(kernel_pagemap, addr, phys, PAGE_PRESENT | PAGE_WRITE | PAGE_NX);
    }

    for (uint64_t gib4 = 0; gib4 < 0x100000000; gib4 += PAGE_SIZE)
    {
        amd64_paging_map(kernel_pagemap, (uint64_t)HIGHER_HALF(gib4), gib4,
                         PAGE_PRESENT | PAGE_WRITE);
    }

    for (uint64_t i = 0; i < memmap->entry_count; i++)
    {
        if (!memmap->entries[i]->base || !memmap->entries[i]->length)
        {
            continue;
        }

        uint64_t base = ALIGN_DOWN(memmap->entries[i]->base, PAGE_SIZE);
        uint64_t end  = ALIGN_UP(memmap->entries[i]->base + memmap->entries[i]->length, PAGE_SIZE);

        for (uint64_t addr = base; addr < end;)
        {
            uint64_t virt = (uint64_t)HIGHER_HALF(addr);
            amd64_paging_map(kernel_pagemap, virt, addr, PAGE_PRESENT | PAGE_WRITE | PAGE_NX);
            addr += PAGE_SIZE;
        }
    }

    set_pagemap(kernel_pagemap);
}

int amd64_paging_map(uint64_t *pagemap, uint64_t virt, uint64_t phys, uint64_t flags)
{
}
