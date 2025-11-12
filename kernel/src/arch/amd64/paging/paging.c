#include "paging.h"
#include "lib/align.h"
#include "mem/mmutil.h"
#include "mem/pmm.h"
#include "util/log.h"
#include <stdint.h>

void _map(uint64_t *pml4, uint64_t physical, uint64_t virtual, uint64_t flags);
uint64_t *_get_or_create_pmlt(uint64_t *pmlt, uint64_t pmlt_index, uint64_t flags);

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
        log_warn("%i", p);
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

    uint64_t *pml3 = _get_or_create_pmlt(pml4, pml4_idx, 0b111);
    uint64_t *pml2 = _get_or_create_pmlt(pml3, pml3_idx, 0b111);
    uint64_t *pml1 = _get_or_create_pmlt(pml2, pml2_idx, 0b111);

    pml1[pml1_idx] = PAGE_GET_ADDR(physical) | flags;
    __asm__ volatile("invlpg (%0)" : : "r"(virtual) : "memory");

    log_debug("Mapped phys 0x%llx -> virt 0x%llx (pml1[%llx] = 0x%llx)", physical, virtual,
              pml1_idx, pml1[pml1_idx]);
}

uint64_t *_get_or_create_pmlt(uint64_t *pmlt, uint64_t pmlt_index, uint64_t flags)
{
    if (!(pmlt[pmlt_index] & PMLE_PRESENT))
    {
        log_debug("Table 0x%llp entry 0x%llx is not present, creating it...", pmlt, pmlt_index);
        pmlt[pmlt_index] = (uint64_t)palloc(1, 0) | flags;
    }
    else
    {
        log_debug("Table 0x%llp entry 0x%llx contents: 0x%llx flags: 0x%llx", pmlt, pmlt_index,
                  pmlt[pmlt_index], flags);
    }
    uint64_t page_addr = PAGE_GET_ADDR(pmlt[pmlt_index]);
    if (!page_addr)
    {
        log_warn("Page entry address is NULL\n");
    }
    return (uint64_t *)(HIGHER_HALF(page_addr));
}
