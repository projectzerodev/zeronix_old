#include "keyboard.h"
#include "arch/amd64/isr/isr.h"
#include "arch/amd64/pic/pic.h"
#include "arch/x86/io.h"
#include "util/log.h"
#include <stdint.h>

#define PS2_DATA_PORT 0x60

static void ps2_keyboard_irq_handler(void *context);

void ps2_keyboard_init()
{
    amd64_isr_register_handler(32 + 1, ps2_keyboard_irq_handler);
    amd64_pic_unmask(1);
    log_debug("Initialized PS/2 Keyboard");
}

static void ps2_keyboard_irq_handler(void *context)
{
    (void)context;
    uint8_t sc = x86_inb(PS2_DATA_PORT);
    log_warn("Unhandled PS/2 interrupt with scancode: 0x%x", sc);
    amd64_pic_send_eoi(1);
}
