#include "idt.h"
#include "arch/amd64/gdt/gdt.h"
#include "arch/amd64/isr/isr.h"
#include "hal/cpu.h"
#include "utils/log.h"
#include <stdint.h>

typedef struct
{
    uint16_t offset_low;
    uint16_t kernel_cs;
    uint8_t ist;
    uint8_t attributes;
    uint16_t offset_mid;
    uint32_t offset_high;
    uint32_t reserved;
} __attribute__((packed)) idt_entry_t;

typedef struct
{
    uint16_t limit;
    idt_entry_t *base;
} __attribute__((packed)) idtr_t;

__attribute__((aligned(0x10))) static idt_entry_t idt[IDT_MAX_DESCRIPTORS];

idtr_t idtr = {sizeof(idt) - 1, idt};

extern void amd64_idt_load(idtr_t *pointer);

void amd64_idt_init()
{
    log_trace("IDTR Base:  %p", (void *)idt);
    log_trace("IDTR Limit: %x", idtr.limit);

    for (uint16_t vector = 0; vector < IDT_MAX_DESCRIPTORS; vector++)
    {
        amd64_idt_set_gate(vector, amd64_isr_stub_table[vector], GDT_CODE_SEGMENT,
                           0x8E); // Present, INT gate
    }

    amd64_idt_load(&idtr);

    // asm("sti");
}

void amd64_idt_set_gate(uint8_t index, void *base, uint16_t selector, uint8_t flags)
{
    idt[index].offset_low  = (uint64_t)base & 0xFFFF;
    idt[index].kernel_cs   = selector;
    idt[index].ist         = 0;
    idt[index].attributes  = flags;
    idt[index].offset_mid  = ((uint64_t)base >> 16) & 0xFFFF;
    idt[index].offset_high = ((uint64_t)base >> 32) & 0xFFFFFFFF;
    idt[index].reserved    = 0;
}
