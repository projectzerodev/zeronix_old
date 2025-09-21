#pragma once

#define COLOR_RESET "\033[0m"

typedef enum
{
    LOG_FATAL,
    LOG_ERROR,
    LOG_WARN,
    LOG_INFO,
    LOG_DEBUG,
    LOG_TRACE,
} log_level_t;

void _log(log_level_t level, const char *format, ...);

#define log_fatal(format, ...) _log(LOG_FATAL, format, ##__VA_ARGS__)
#define log_error(format, ...) _log(LOG_ERROR, format, ##__VA_ARGS__)
#define log_warn(format, ...)  _log(LOG_WARN, format, ##__VA_ARGS__)
#define log_info(format, ...)  _log(LOG_INFO, format, ##__VA_ARGS__)
#define log_trace(format, ...) _log(LOG_TRACE, format, ##__VA_ARGS__)
