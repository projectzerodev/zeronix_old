#include "log.h"
#include "core/stdio.h"
#include <stdarg.h>

const char *level_tags[] = {"FATAL", "ERROR", "WARN ",
                            "INFO ", "DEBUG", "TRACE"};

const char *level_colors[] = {"\x1b[1;31m", "\x1b[31m", "\x1b[93m",
                              "\x1b[32m",   "\x1b[36m", "\x1b[90m"};

void log(log_level_t level, const char *format, ...) {
    va_list args;
    va_start(args);

    kprintf("%s%s%s ", level_colors[level], level_tags[level], COLOR_RESET);
    kvprintf(format, args);
    kprintf("\n");
    va_end(args);
}
