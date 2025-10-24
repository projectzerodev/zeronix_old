#include "paging.h"
#include "core/panic.h"
#include "mem/mmutil.h"
#include "mem/pmm.h"
#include "util/log.h"
#include <stddef.h>
#include <string.h>

#define PAGE_FRAME_MASK 0x000FFFFFFFFFF000ULL
#define PML_INDEX_MASK  0x1ffULL
#define PML_SHIFT_L1    12
#define PML_SHIFT_L2    21
#define PML_SHIFT_L3    30
#define PML_SHIFT_L4    39

pagetable_t *kernel_pagemap = NULL;

void amd64_paging_init()
{
    if (kernel_pagemap)
    {
        log_warn("Kernel pagemap is already initialized");
        return;
    }
    uintptr_t new_pagemap = (uintptr_t)palloc(1, false);
    if (!new_pagemap)
    {
        panic("Failed to allocate new kernel pagemap");
    }
    memset((void *)HIGHER_HALF(new_pagemap), 0, PAGE_SIZE);
    log_debug("Allocated new kernel pagemap at 0x%x", new_pagemap);
}
