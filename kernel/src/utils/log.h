#pragma once

typedef enum {
    FATAL,
    ERROR,
    WARN,
    INFO,
    DEBUG,
    TRACE,
} log_level_t;

void log(log_level_t level, const char *format, ...);
