#pragma once
#include <stdint.h>

#define PAGE_SIZE 0x1000

typedef struct
{
    uint64_t entries[512];
} pagetable_t;

void amd64_paging_init();
