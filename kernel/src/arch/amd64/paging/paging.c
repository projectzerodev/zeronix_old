#include "paging.h"
#include "lib/align.h"
#include "mem/mmutil.h"
#include "mem/pmm.h"
#include "util/log.h"
#include <stdint.h>

void _map(uint64_t *åml4, uint64_t physical, uint64_t virtual, uint64_t flags);

void amd64_paging_init()
{
    uint64_t *kernel_pml4 = palloc(1, true);
    log_debug("Limine's PML4 sits at: 0x%llp", get_pml4());

    log_debug("__kernel_start:\t 0x%p", &__kernel_start);
    log_debug("__kernel_text:\t 0x%p -> 0x%p", &__kernel_text_start, &__kernel_text_end);
    log_debug("__kernel_data:\t 0x%p -> 0x%p", &__kernel_data_start, &__kernel_data_end);
    log_debug("__kernel_rodata:\t 0x%p -> 0x%p", &__kernel_rodata_start, &__kernel_rodata_end);
    log_debug("__limine_requests: 0x%p -> 0x%p", &__limine_requests_start, &__limine_requests_end);
    log_debug("__kernel_end:\t 0x%p", &__kernel_end);

    uint64_t kernel_text_length = (uint64_t)&__kernel_text_end - (uint64_t)&__kernel_text_start;
    log_debug("Mapping kernel section: .text");
    amd64_paging_map_region(kernel_pml4, (uint64_t)&__kernel_text_start - VIRT_BASE + PHYS_BASE,
                            (uint64_t)&__kernel_text_start, kernel_text_length,
                            PMLE_PRESENT | PMLE_WRITE);
}

void amd64_paging_map_region(uint64_t *pml4, uint64_t phys_start, uint64_t virt_start,
                             uint64_t length, uint64_t flags)
{

    log_debug("Mapping address range 0x%llx-0x%llx to 0x%llx-0x%llx", phys_start,
              phys_start + length, virt_start, virt_start + length);

    uint64_t pages = ROUND_UP(length, PAGE_SIZE) / PAGE_SIZE;
    for (uint64_t p = 0; p < pages; p++)
    {
        uint64_t phys = phys_start + (p * PAGE_SIZE);
        uint64_t virt = virt_start + (p * PAGE_SIZE);
        _map(pml4, phys, virt, flags);
    }
}

void _map(uint64_t *pml4, uint64_t physical, uint64_t virtual, uint64_t flags)
{
    uint64_t pml4_idx = PML4_INDEX(virtual);
    uint64_t pml3_idx = PML3_INDEX(virtual);
    uint64_t pml2_idx = PML2_INDEX(virtual);
    uint64_t pml1_idx = PML1_INDEX(virtual);
}
