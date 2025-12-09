#pragma once
#include "limine.h"
#include <stddef.h>
#include <stdint.h>

#define PAGE_SIZE 0x1000

/**
 * @brief Initializes the Physical Memory Manager
 *
 * @param memmap_request Pointer to the Limine memory map request.
 * @param hhdm_request Pointer to the Limine HHDM request.
 */
void pmm_init(volatile struct limine_memmap_request *memmap_request,
              volatile struct limine_hhdm_request *hhdm_request);

/**
 * @brief Allocates a physical frame
 *
 * @param n The amount of frames to allocate
 * @param higher_half Specifies if the HHDM offset should be added to the pointer returned.
 * @return Physical (or virtual if `higher_half` is true) address of the alloacted frame.
 */
void *palloc(size_t n, bool higher_half);

/**
 * @brief Frees a physical frame
 *
 * @param addr The address of the frame (can be either virtual or physical).
 * @param n The amount of frames to free.
 */
void pfree(void *addr, size_t n);
