#pragma once

#define GDT_CODE_SEGMENT 0x8
#define GDT_DATA_SEGMENT 0x10

/**
 * @brief Loads the Global Descriptor Table.
 */
void amd64_gdt_init();
