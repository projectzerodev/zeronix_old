#include "paging.h"
#include "gen/autoconf.h"
#include "lib/align.h"
#include "mem/mmutil.h"
#include "mem/pmm.h"
#include "util/log.h"
#include <stdint.h>
#include <string.h>

uint64_t *global_kernel_pml4;

void _map(uint64_t *pml4, uint64_t physical, uint64_t virtual, uint64_t flags);
void _unmap(uint64_t *pml4, uint64_t virtual);
uint64_t *_get_or_create_pmlt(uint64_t *pmlt, uint64_t pmlt_index, uint64_t flags);
uint64_t *_get_pmlt(uint64_t *pmlt, uint64_t pmlt_index);

void amd64_paging_init(volatile struct limine_memmap_request *memmap_request)
{
    uint64_t *kernel_pml4 = palloc(1, true);
#ifdef PAGING_DEBUG
    log_debug("Limine's PML4 sits at: 0x%llp", get_pml4());

    log_debug("__kernel_start:\t 0x%p", &__kernel_start);
    log_debug("__kernel_text:\t 0x%p -> 0x%p", &__kernel_text_start, &__kernel_text_end);
    log_debug("__kernel_data:\t 0x%p -> 0x%p", &__kernel_data_start, &__kernel_data_end);
    log_debug("__kernel_rodata:\t 0x%p -> 0x%p", &__kernel_rodata_start, &__kernel_rodata_end);
    log_debug("__limine_requests: 0x%p -> 0x%p", &__limine_requests_start, &__limine_requests_end);
    log_debug("__kernel_end:\t 0x%p", &__kernel_end);
#endif // PAGING_DEBUG

#ifdef PAGING_DEBUG
    log_debug("Mapping kernel section: .text");
#endif // PAGING_DEBUG

    uint64_t kernel_text_length = (uint64_t)&__kernel_text_end - (uint64_t)&__kernel_text_start;
    amd64_paging_map_region(kernel_pml4, (uint64_t)&__kernel_text_start - VIRT_BASE + PHYS_BASE,
                            (uint64_t)&__kernel_text_start, kernel_text_length,
                            PMLE_PRESENT | PMLE_WRITE);

#ifdef PAGING_DEBUG
    log_debug("Mapping kernel section: .rodata");
#endif // PAGING_DEBUG
    uint64_t kernel_rodata_length =
        (uint64_t)&__kernel_rodata_end - (uint64_t)&__kernel_rodata_start;
    amd64_paging_map_region(kernel_pml4, (uint64_t)&__kernel_rodata_start - VIRT_BASE + PHYS_BASE,
                            (uint64_t)&__kernel_rodata_start, kernel_rodata_length,
                            PMLE_PRESENT | PMLE_NOT_EXECUTABLE);

#ifdef PAGING_DEBUG
    log_debug("Mapping kernel section: .data (and misc)");
#endif // PAGING_DEBUG
    uint64_t kernel_data_length  = (uint64_t)&__kernel_data_end - (uint64_t)&__kernel_data_start;
    uint64_t kernel_other_length = (uint64_t)&__kernel_end - (uint64_t)&__kernel_data_end;
    amd64_paging_map_region(kernel_pml4, (uint64_t)&__kernel_data_start - VIRT_BASE + PHYS_BASE,
                            (uint64_t)&__kernel_data_start,
                            kernel_data_length + kernel_other_length,
                            PMLE_PRESENT | PMLE_WRITE | PMLE_NOT_EXECUTABLE);

#ifdef PAGING_DEBUG
    log_debug("Mapping Limine requests");
#endif // PAGING_DEBUG
    uint64_t limine_requests_length =
        (uint64_t)&__limine_requests_end - (uint64_t)&__limine_requests_end;
    amd64_paging_map_region(kernel_pml4, (uint64_t)&__limine_requests_start - VIRT_BASE + PHYS_BASE,
                            (uint64_t)&__limine_requests_start,
                            kernel_data_length + limine_requests_length,
                            PMLE_PRESENT | PMLE_WRITE | PMLE_NOT_EXECUTABLE);

#ifdef PAGING_DEBUG
    log_debug("Mapping the Higher Half");
#endif // PAGING_DEBUG
    for (uint64_t i = 0; i < memmap_request->response->entry_count; i++)
    {
        struct limine_memmap_entry *e = memmap_request->response->entries[i];
        amd64_paging_map_region(kernel_pml4, e->base, (uint64_t)HIGHER_HALF(e->base), e->length,
                                PMLE_PRESENT | PMLE_WRITE);
    }

#ifdef PAGING_DEBUG
    log_debug("Zeronix PML4 sits at: %llp", kernel_pml4);
#endif // PAGING_DEBUG
    global_kernel_pml4 = (uint64_t *)PHYSICAL(kernel_pml4);
    load_pml4(global_kernel_pml4);
    log_info("Initialized Paging");
}

void amd64_paging_map_region(uint64_t *pml4, uint64_t phys_start, uint64_t virt_start,
                             uint64_t length, uint64_t flags)
{
#ifdef PAGING_DEBUG
    log_debug("Mapping address range 0x%llx-0x%llx to 0x%llx-0x%llx", phys_start,
              phys_start + length, virt_start, virt_start + length);
#endif // PAGING_DEBUG

    uint64_t pages = ROUND_UP(length, PAGE_SIZE) / PAGE_SIZE;
    for (uint64_t p = 0; p < pages; p++)
    {
        uint64_t phys = phys_start + (p * PAGE_SIZE);
        uint64_t virt = virt_start + (p * PAGE_SIZE);
        _map(pml4, phys, virt, flags);
    }
}

void amd64_paging_unmap_region(uint64_t *pml4, uint64_t virt_start, uint64_t length)
{
    uint64_t pages = ROUND_UP(length, PAGE_SIZE) / PAGE_SIZE;
#ifdef PAGING_DEBUG
    log_debug("Unmapping address range 0x%llx-0x%llx", virt_start, virt_start + length);
#endif // PAGING_DEBUG
    for (uint64_t i = 0; i < pages; i++)
    {
        uint64_t virt = virt_start + (i * PAGE_SIZE);
        _unmap(pml4, virt);
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

#ifdef PAGING_DEBUG
    log_debug("Mapped phys 0x%llx -> virt 0x%llx (pml1[%llx] = 0x%llx)", physical, virtual,
              pml1_idx, pml1[pml1_idx]);
#endif // PAGING_DEBUG
}

void _unmap(uint64_t *pml4, uint64_t virtual)
{
    uint64_t pml4_idx = PML4_INDEX(virtual);
    uint64_t pml3_idx = PML3_INDEX(virtual);
    uint64_t pml2_idx = PML2_INDEX(virtual);
    uint64_t pml1_idx = PML1_INDEX(virtual);

    uint64_t *pml3 = _get_pmlt(pml4, pml4_idx);
    uint64_t *pml2 = _get_pmlt(pml3, pml3_idx);
    uint64_t *pml1 = _get_pmlt(pml2, pml2_idx);

    pml1[pml1_idx] = 0x0;
    __asm__ volatile("invlpg (%0)" : : "r"(virtual) : "memory");

#ifdef PAGING_DEBUG
    log_debug("Unmapped virt 0x%llx", virtual);
#endif // PAGING_DEBUG
}

uint64_t *_get_or_create_pmlt(uint64_t *pmlt, uint64_t pmlt_index, uint64_t flags)
{
    bool newly_created = false;
    if (!(pmlt[pmlt_index] & PMLE_PRESENT))
    {
#ifdef PAGING_DEBUG
        log_debug("Table 0x%llp entry 0x%llx is not present, creating it...", pmlt, pmlt_index);
#endif // PAGING_DEBUG
        pmlt[pmlt_index] = (uint64_t)palloc(1, 0) | flags;
        newly_created    = true;
    }
    else
    {
#ifdef PAGING_DEBUG
        log_debug("Table 0x%llp entry 0x%llx contents: 0x%llx flags: 0x%llx", pmlt, pmlt_index,
                  pmlt[pmlt_index], flags);
#endif // PAGING_DEBUG
    }
    uint64_t page_addr = PAGE_GET_ADDR(pmlt[pmlt_index]);
    if (!page_addr)
    {
        log_warn("Page entry address is NULL\n");
    }
    uint64_t *table_vaddr = (uint64_t *)(HIGHER_HALF(page_addr));
    if (newly_created)
    {
        memset(table_vaddr, 0, PAGE_SIZE);
    }
    return table_vaddr;
}

uint64_t *_get_pmlt(uint64_t *pmlt, uint64_t pmlt_index)
{
    uint64_t page_addr = PAGE_GET_ADDR(pmlt[pmlt_index]);
    if (!page_addr)
    {
        log_warn("Page entry address is NULL\n");
    }
    return (uint64_t *)(HIGHER_HALF(page_addr));
}
