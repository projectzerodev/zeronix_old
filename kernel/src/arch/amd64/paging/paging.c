#include "paging.h"
#include "core/panic.h"

void amd64_paging_fault_handler(void *context)
{
    (void)context;
    panic("Page Fault (Exception: 0xe)");
}
