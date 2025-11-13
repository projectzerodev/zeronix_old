#include "drivers/ps2/keyboard/keyboard.h"
#include "arch/amd64/isr/isr.h"
#include "arch/amd64/pic/pic.h"
#include "arch/x86/io.h"
#include "util/kprintf.h"
#include "util/log.h"
#include <stdint.h>

#define PS2_DATA_PORT   0x60
#define PS2_STATUS_PORT 0x64


void ps2_keyboard_init()
{
    amd64_isr_register_handler(32 + 1, keyboard_irq_handler);
    amd64_pic_unmask(1);
    log_debug("Initialized PS/2 Keyboard");
}
void keyboard_irq_handler(void *ctx)
{
    uint8_t sc = x86_inb(PS2_DATA_PORT);
    if (sc < 0x80 || sc > 0xD8) {
        ps2_keyboard_getchar(sc);
    }
    amd64_pic_send_eoi(1);
}
void ps2_keyboard_getchar(uint8_t scancode)
{
    switch (scancode) {
        case 0x01:
            kprintf("ESC");
            break;
        case 0x02:
            kprintf("1");
            break;
        case 0x03:
            kprintf("2");
            break;
        case 0x04:
            kprintf("3");
            break;
        case 0x05:
            kprintf("4");
            break;
        case 0x06:
            kprintf("5");
            break;
        case 0x07:
            kprintf("6");
            break;
        case 0x08:
            kprintf("7");
            break;
        case 0x09:
            kprintf("8");
            break;
        case 0x0a:
            kprintf("9");
            break;
        case 0x0b:
            kprintf("0");
            break;
        case 0x0c:
            kprintf("-");
            break;
        case 0x0d:
            kprintf("=");
            break;
        case 0x0e:
            kprintf("Backspace");
            break;
        case 0x0f:
            kprintf("Tab");
            break;
        case 0x10:
            kprintf("Q");
            break;
        case 0x11:
            kprintf("W");
            break;
        case 0x12:
            kprintf("E");
            break;
        case 0x13:
            kprintf("R");
            break;
        case 0x14:
            kprintf("T");
            break;
        case 0x15:
            kprintf("Y");
            break;
        case 0x16:
            kprintf("U");
            break;
        case 0x17:
            kprintf("I");
            break;
        case 0x18:
            kprintf("O");
            break;
        case 0x19:
            kprintf("P");
            break;
        case 0x1a:
            kprintf("[");
            break;
        case 0x1b:
            kprintf("]");
            break;
        case 0x1c:
            kprintf("Enter");
            break;
        case 0x1d:
            kprintf("Left Ctrl");
            break;
        case 0x1e:
            kprintf("A");
            break;
        case 0x1f:
            kprintf("S");
            break;
        case 0x20:
            kprintf("D");
            break;
        case 0x21:
            kprintf("F");
            break;
        case 0x22:
            kprintf("G");
            break;
        case 0x23:
            kprintf("H");
            break;
        case 0x24:
            kprintf("J");
            break;
        case 0x25:
            kprintf("K");
            break;
        case 0x26:
            kprintf("L");
            break;
        case 0x27:
            kprintf(";");
            break;
        case 0x28:
            kprintf("'");
            break;
        case 0x29:
            kprintf("`");
            break;
        case 0x2a:
            kprintf("Left Shift");
            break;
        case 0x2b:
            kprintf("\\");
            break;
        case 0x2c:
            kprintf("Z");
            break;
        case 0x2d:
            kprintf("X");
            break;
        case 0x2e:
            kprintf("C");
            break;
        case 0x2f:
            kprintf("V");
            break;
        case 0x30:
            kprintf("B");
            break;
        case 0x31:
            kprintf("N");
            break;
        case 0x32:
            kprintf("M");
            break;
        case 0x33:
            kprintf(",");
            break;
        case 0x34:
            kprintf(".");
            break;
        case 0x35:
            kprintf("/");
            break;
        case 0x36:
            kprintf("Right Shift");
            break;
        case 0x37:
            kprintf("Keypad * Pressed");
            break;
        case 0x38:
            kprintf("Left Alt");
            break;
        case 0x39:
            kprintf("Space");
            break;
        case 0x3a:
            kprintf("Caps Lock");
            break;
        case 0x3b:
            kprintf("F1");
            break;
        case 0x3c:
            kprintf("F2");
            break;
        case 0x3d:
            kprintf("F3");
            break;
        case 0x3e:
            kprintf("F4");
            break;
        case 0x3f:
            kprintf("F5");
            break;
        case 0x40:
            kprintf("F6");
            break;
        case 0x41:
            kprintf("F7");
            break;
        case 0x42:
            kprintf("F8");
            break;
        case 0x43:
            kprintf("F9");
            break;
        case 0x44:
            kprintf("F10");
            break;
        default:
            kprintf("?");
            break;
    }
}