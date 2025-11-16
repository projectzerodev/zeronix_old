#include "vmm.h"
#include "arch/amd64/paging/paging.h"
#include "lib/align.h"
#include "mem/pmm.h"
#include "util/log.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

vmm_context_t *kernel_vmm_context;

static vmm_node_t *vmm_context_list = NULL;
static vmm_node_t *vmm_object_list  = NULL;

void *vmm_list_node_alloc(size_t size)
{
    size_t aligned = ROUND_UP(size, PAGE_SIZE);

    vmm_node_t *node = (vmm_node_t *)palloc(aligned / PAGE_SIZE, true);

    node->length = aligned;
    return node;
}

void *vmm_node_alloc(vmm_node_t **root, size_t size)
{
    void *node = NULL;

    // If there is no root, allocate it
    if (!(*root))
    {
        (*root) = (vmm_node_t *)vmm_list_node_alloc(size);
    }

    vmm_node_t *node_current;
    vmm_node_t *node_previous;

    // Find a block large enough to hold the node
    for (node_current = (*root); node_current->next != NULL; node_current = node_current->next)
    {
        if (node_current->length >= size)
        {
            break;
        }

        if (!node_current->next)
        {
            node_current->next = vmm_list_node_alloc(size);
        }
    }

    node                 = node_current;
    node_current->length = sizeof(vmm_node_t);

    if (node_current != (*root))
    {
        // Find the block before the current node
        for (node_previous = (*root); node_previous != node_current;
             node_previous = node_previous->next)
            ;

        // Shift the node
        node_previous->next += size;
        memcpy(node_previous->next, node_current, sizeof(vmm_node_t));
    }
    else
    {
        (*root) = (void *)(*root) + size;
        memcpy((*root), node_current, sizeof(vmm_node_t));
    }

    return node;
}

vmm_context_t *vmm_context_alloc()
{
    return (vmm_context_t *)vmm_node_alloc(&vmm_context_list, sizeof(vmm_context_t));
}

vmm_object_t *vmm_object_alloc()
{
    return (vmm_object_t *)vmm_node_alloc(&vmm_object_list, sizeof(vmm_object_t));
}

vmm_object_t *vmm_object_init(uint64_t base, size_t length, uint64_t flags)
{
    vmm_object_t *object = vmm_object_alloc();

    object->base   = base;
    object->flags  = flags;
    object->length = length;
    object->next   = NULL;

    return object;
}

vmm_context_t *vmm_context_init(uint64_t *pml4, uint64_t flags)
{
    vmm_context_t *context = vmm_context_alloc();

    context->pml4 = pml4;
    context->root = vmm_object_init(0x1000, 1, flags);

    return context;
}

void vmm_init()
{
    kernel_vmm_context = vmm_context_init((uint64_t *)get_pml4(), VMO_PRESENT | VMO_RW);
    log_debug("Initialized VMM");
}
