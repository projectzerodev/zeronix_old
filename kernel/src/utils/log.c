#include "log.h"
#include "core/stdio.h"
#include <stdarg.h>

const char *level_tags[] = {"FATAL", "ERROR", "WARN ",
                            "INFO ", "DEBUG", "TRACE"};

void log(log_level_t level, const char *format, ...) {
    va_list args;
    va_start(args);

    kprintf("%s ", level_tags[level]);
    kvprintf(format, args);
    kprintf("\n");
    va_end(args);
}
