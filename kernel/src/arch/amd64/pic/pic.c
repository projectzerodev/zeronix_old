#include "pic.h"
#include "arch/x86/io.h"
#include "util/log.h"
#include <stdint.h>

#define PIC1_CMD_PORT  0x20
#define PIC1_DATA_PORT 0x21
#define PIC2_CMD_PORT  0xA0
#define PIC2_DATA_PORT 0xA1

#define PIC1_OFFSET 0x20
#define PIC2_OFFSET 0x28

#define PIC_ICW4 0x01

#define PIC_CMD_END_OF_INTERRUPT 0x20

static uint16_t pic_mask;

void amd64_pic_init()
{
    amd64_pic_set_mask(0xffff);

    // 0x01: We wan't to send 4 initialization words
    // 0x10: Begin the initialization sequence
    x86_outb(PIC1_CMD_PORT, 0x01 | 0x10);
    x86_iowait();
    x86_outb(PIC2_CMD_PORT, 0x01 | 0x10);
    x86_iowait();

    // Set the offsets
    x86_outb(PIC1_DATA_PORT, PIC1_OFFSET);
    x86_iowait();
    x86_outb(PIC2_DATA_PORT, PIC2_OFFSET);
    x86_iowait();

    // 0x04: The place on which PIC1 has a slave
    // 0x20: The place on which PIC1 is connected to the master
    x86_outb(PIC1_DATA_PORT, 0x04);
    x86_iowait();
    x86_outb(PIC2_DATA_PORT, 0x02);
    x86_iowait();

    // We are in 8086 mode with no automatic EOI
    x86_outb(PIC1_DATA_PORT, PIC_ICW4);
    x86_iowait();
    x86_outb(PIC2_DATA_PORT, PIC_ICW4);
    x86_iowait();

    amd64_pic_set_mask(0xffff);

    log_debug("Initialized PIC");
}

void amd64_pic_send_eoi(int irq)
{
    if (irq >= 8)
    {
        x86_outb(PIC2_CMD_PORT, PIC_CMD_END_OF_INTERRUPT);
    }
    x86_outb(PIC1_CMD_PORT, PIC_CMD_END_OF_INTERRUPT);
}

void amd64_pic_set_mask(uint16_t new_mask)
{
    pic_mask = new_mask;
    x86_outb(PIC1_DATA_PORT, pic_mask & 0xFF);
    x86_iowait();
    x86_outb(PIC2_DATA_PORT, pic_mask >> 8);
    x86_iowait();
}

void amd64_pic_mask(int irq)
{
    amd64_pic_set_mask(pic_mask | (1 << irq));
}

void amd64_pic_unmask(int irq)
{
    amd64_pic_set_mask(pic_mask & ~(1 << irq));
}
