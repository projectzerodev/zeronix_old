#pragma once

#define GDT_CODE_SEGMENT 0x8
#define GDT_DATA_SEGMENT 0x10

void amd64_gdt_init();
