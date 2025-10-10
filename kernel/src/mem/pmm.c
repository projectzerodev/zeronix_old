#include "pmm.h"
#include "hal/cpu.h"
#include "lib/align.h"
#include "lib/bitmap.h"
#include "lib/spinlock.h"
#include "limine.h"
#include "util/log.h"
#include <stdint.h>
#include <string.h>

#define BITMAP_WORD_SIZE (sizeof(uint64_t) * 8)

spinlock_t pmm_lock;
uint8_t *bitmap;
uint64_t bitmap_pages; // The amount of pages in memory
uint64_t bitmap_size;  // The amount of bytes the bitmap uses

static inline bool is_aligned(physaddr_t addr, size_t align)
{
    return ((uintptr_t)addr % align) == 0;
}

void pmm_init(volatile struct limine_memmap_request *memmap_request,
              volatile struct limine_hhdm_request *hhdm_request)
{
    if (!memmap_request->response)
    {
        log_error("Failed to fetch Limine memory map. Halting...");
        halt_loop();
    }

    spinlock_init(&pmm_lock);

    struct limine_memmap_response *memmap = memmap_request->response;
    struct limine_hhdm_response *hhdm     = hhdm_request->response;

    uint64_t high;

    for (uint64_t i = 0; i < memmap->entry_count; i++)
    {
        struct limine_memmap_entry *e = memmap->entries[i];
        if (e->type == LIMINE_MEMMAP_USABLE)
        {
            uint64_t top = e->base + e->length;
            if (top > high)
            {
                high = top;
            }
            log_debug("Usable memory region: 0x%.16llx -> 0x%.16llx", e->base, top);
        }
    }

    bitmap_pages = high / PAGE_SIZE;
    bitmap_size  = ALIGN_UP(bitmap_pages / 8, PAGE_SIZE);

    for (uint64_t i = 0; i < memmap->entry_count; i++)
    {
        struct limine_memmap_entry *e = memmap->entries[i];
        if (e->type == LIMINE_MEMMAP_USABLE && e->length >= bitmap_size)
        {
            bitmap = (uint8_t *)(e->base + hhdm->offset);
            memset(bitmap, 0xFF, bitmap_size);
            e->base   += bitmap_size;
            e->length -= bitmap_size;
            break;
        }
    }

    for (uint64_t i = 0; i < memmap->entry_count; i++)
    {
        struct limine_memmap_entry *e = memmap->entries[i];
        if (e->type == LIMINE_MEMMAP_USABLE)
        {
            for (uint64_t j = e->base; j < e->base + e->length; j += PAGE_SIZE)
            {
                if ((j / PAGE_SIZE) < bitmap_pages)
                {
                    bitmap_clear(bitmap, j / PAGE_SIZE);
                }
            }
        }
    }
}

// If you wan't to just add the HHDM offset for the virtual address
physaddr_t palloc(size_t n)
{
    if (n == 0)
    {
        return 0;
    }

    spinlock_acquire(&pmm_lock);

    uint64_t word_count    = (bitmap_pages + BITMAP_WORD_SIZE - 1) / BITMAP_WORD_SIZE;
    uint64_t *bitmap_words = (uint64_t *)bitmap;

    for (uint64_t i = 0; i < word_count; i++)
    {
        if (bitmap_words[i] != UINT64_MAX)
        {
            uint64_t start_bit   = i * BITMAP_WORD_SIZE;
            uint64_t consecutive = 0;

            for (uint64_t j = 0; j < BITMAP_WORD_SIZE && start_bit + j < bitmap_pages; j++)
            {
                if (!bitmap_get(bitmap, start_bit + j))
                {
                    if (++consecutive == n)
                    {
                        for (uint64_t k = 0; k < n; k++)
                        {
                            bitmap_set(bitmap, start_bit + j - n + 1 + k);
                        }

                        physaddr_t addr = (physaddr_t)((start_bit + j - n + 1) * PAGE_SIZE);
                        memset((void *)addr, 0, n * PAGE_SIZE);
                        spinlock_release(&pmm_lock);
                        return addr;
                    }
                }
                else
                {
                    consecutive = 0;
                }
            }
        }
    }

    spinlock_release(&pmm_lock);
    return 0;
}

void pfree(physaddr_t addr, size_t n)
{
    if (!is_aligned(addr, PAGE_SIZE))
    {
        return;
    }

    spinlock_acquire(&pmm_lock);

    uint64_t start = (uint64_t)addr / PAGE_SIZE;

    if (start + n > bitmap_pages)
    {
        spinlock_release(&pmm_lock);
        log_warn("Tried to free %i non-existing page(s) at 0x%.16llx", n, addr);
        return;
    }

    for (size_t i = 0; i < n; i++)
    {
        if (bitmap_get(bitmap, start + i))
        {
            bitmap_clear(bitmap, start + i);
        }
    }

    spinlock_release(&pmm_lock);
}
