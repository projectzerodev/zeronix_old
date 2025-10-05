#include "gdt.h"
#include "utils/log.h"
#include <stdint.h>

typedef struct
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t flags_limit_high;
    uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct
{
    uint16_t limit; // sizeof(gdt) - 1
    gdt_entry_t *entry;
} __attribute__((packed)) gdtr_t;

typedef enum
{
    GDT_ACCESS_CODE_READABLE  = 0x02,
    GDT_ACCESS_DATA_WRITEABLE = 0x02,

    GDT_ACCESS_CODE_CONFORMING       = 0x04,
    GDT_ACCESS_DATA_DIRECTION_NORMAL = 0x00,
    GDT_ACCESS_DATA_DIRECTION_DOWN   = 0x04,

    GDT_ACCESS_DATA_SEGMENT = 0x10,
    GDT_ACCESS_CODE_SEGMENT = 0x18,

    GDT_ACCESS_DESCRIPTOR_TSS = 0x00,

    GDT_ACCESS_RING0 = 0x00,
    GDT_ACCESS_RING1 = 0x20,
    GDT_ACCESS_RING2 = 0x40,
    GDT_ACCESS_RING3 = 0x60,

    GDT_ACCESS_PRESENT = 0x80,
} GDT_ACCESS;

typedef enum
{
    GDT_FLAG_64BIT = 0x20,
    GDT_FLAG_32BIT = 0x40,
    GDT_FLAG_16BIT = 0x00,

    GDT_FLAG_GRANULARITY_1B = 0x00,
    GDT_FLAG_GRANULARITY_4K = 0x80,
} GDT_FLAGS;

// Helper macros
#define GDT_LIMIT_LOW(limit)             (limit & 0xFFFF)
#define GDT_BASE_LOW(base)               (base & 0xFFFF)
#define GDT_BASE_MIDDLE(base)            ((base >> 16) & 0xFF)
#define GDT_FLAGS_LIMIT_HI(limit, flags) (((limit >> 16) & 0xF) | (flags & 0xF0))
#define GDT_BASE_HIGH(base)              ((base >> 24) & 0xFF)

#define GDT_ENTRY(base, limit, access, flags)                                                      \
    {GDT_LIMIT_LOW(limit),                                                                         \
     GDT_BASE_LOW(base),                                                                           \
     GDT_BASE_MIDDLE(base),                                                                        \
     access,                                                                                       \
     GDT_FLAGS_LIMIT_HI(limit, flags),                                                             \
     GDT_BASE_HIGH(base)}

gdt_entry_t gdt[] = {
    // Null descriptor
    GDT_ENTRY(0, 0, 0, 0),

    // Kernel 64-bit code segment
    GDT_ENTRY(0, 0xFFFF,
              GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 | GDT_ACCESS_CODE_SEGMENT |
                  GDT_ACCESS_CODE_READABLE,
              GDT_FLAG_64BIT | GDT_FLAG_GRANULARITY_4K),

    // Kernel 64-bit data segment
    GDT_ENTRY(0, 0xFFFF,
              GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 | GDT_ACCESS_DATA_SEGMENT |
                  GDT_ACCESS_DATA_WRITEABLE,
              GDT_FLAG_GRANULARITY_4K),
};

gdtr_t gdtr = {sizeof(gdt) - 1, gdt};

extern void amd64_gdt_load(gdtr_t *pointer, uint16_t code_segment, uint16_t data_segment);

void amd64_gdt_init()
{
    log_trace("GDTR Base:  %p", (void *)gdt);
    log_trace("GDTR Limit: %x", gdtr.limit);

    amd64_gdt_load(&gdtr, GDT_CODE_SEGMENT, GDT_DATA_SEGMENT);
}
