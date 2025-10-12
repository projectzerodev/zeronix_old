#pragma once

void amd64_exceptions_init();

void amd64_paging_fault_handler(void *context);
