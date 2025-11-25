#pragma once
#include <stddef.h>
#include <stdint.h>

#define VMO_PRESENT (1 << 0)
#define VMO_RW      (1 << 1)
#define VMO_USER    (1 << 2)
#define VMO_NX      (1 << 3)

/**
 * @brief Represents a virtual memory range.
 */
typedef struct vmm_object_t
{
    uint64_t base;
    size_t length;
    uint64_t flags;

    struct vmm_object_t *next;
} vmm_object_t;

/**
 * @brief Represents a virtual memory space.
 */
typedef struct
{
    uint64_t *pml4; // Physical address
    vmm_object_t *root;
} vmm_context_t;

/**
 * @brief Represents a single VMO/VMC in memory.
 *
 * This is used so that we don't need to allocate a full page for a single VMO/VMC.
 */
typedef struct vmm_node_t
{
    size_t length;
    struct vmm_node_t *next;
} vmm_node_t;

vmm_context_t *vmm_context_init(uint64_t *pml4, uint64_t flags);
void vmm_init();
