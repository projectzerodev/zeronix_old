#pragma once

#define COLOR_RESET "\033[0m"

typedef enum {
    LOG_FATAL,
    LOG_ERROR,
    LOG_WARN,
    LOG_INFO,
    LOG_DEBUG,
    LOG_TRACE,
} log_level_t;

void log(log_level_t level, const char *format, ...);

#define fatal(format, ...) log(LOG_FATAL, format, ##__VA_ARGS__)
#define error(format, ...) log(LOG_ERROR, format, ##__VA_ARGS__)
#define warn(format, ...)  log(LOG_WARN, format, ##__VA_ARGS__)
#define info(format, ...)  log(LOG_INFO, format, ##__VA_ARGS__)
#define trace(format, ...) log(LOG_TRACE, format, ##__VA_ARGS__)
