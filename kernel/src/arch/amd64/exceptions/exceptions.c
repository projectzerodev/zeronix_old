#include "exceptions.h"
#include "arch/amd64/isr/isr.h"
#include "arch/amd64/paging/paging.h"
#include "util/log.h"

void amd64_exceptions_init()
{
    amd64_isr_register_handler(14, amd64_paging_fault_handler);
    log_debug("Registered exception handlers");
}
