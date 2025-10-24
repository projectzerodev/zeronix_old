#pragma once

#include "util/kprintf.h"

#define LOG_COLOR_DEBUG "\033[94m"
#define LOG_COLOR_INFO  "\033[92m"
#define LOG_COLOR_WARN  "\033[93m"
#define LOG_COLOR_ERROR "\033[91m"
#define LOG_COLOR_RESET "\033[0m"

#ifdef VERBOSE_LOGGING
#define log_debug(fmt, ...)                                                                        \
    kprintf(LOG_COLOR_DEBUG "debug @ %s(): " LOG_COLOR_RESET fmt "\n", __func__, ##__VA_ARGS__)
#define log_info(fmt, ...)                                                                         \
    kprintf(LOG_COLOR_INFO " info @ %s(): " LOG_COLOR_RESET fmt "\n", __func__, ##__VA_ARGS__)
#define log_warn(fmt, ...)                                                                         \
    kprintf(LOG_COLOR_WARN " warn @ %s(): " LOG_COLOR_RESET fmt "\n", __func__, ##__VA_ARGS__)
#define log_error(fmt, ...)                                                                        \
    kprintf(LOG_COLOR_ERROR "error @ %s(): " LOG_COLOR_RESET fmt "\n", __func__, ##__VA_ARGS__)
#else
#define log_debug(fmt, ...)                                                                        \
    kprintf(LOG_COLOR_DEBUG "DEBUG " LOG_COLOR_RESET fmt "\n", ##__VA_ARGS__)
#define log_info(fmt, ...) kprintf(LOG_COLOR_INFO "INFO  " LOG_COLOR_RESET fmt "\n", ##__VA_ARGS__)
#define log_warn(fmt, ...) kprintf(LOG_COLOR_WARN "WARN  " LOG_COLOR_RESET fmt "\n", ##__VA_ARGS__)
#define log_error(fmt, ...)                                                                        \
    kprintf(LOG_COLOR_ERROR "ERROR " LOG_COLOR_RESET fmt "\n", ##__VA_ARGS__)
#endif /* VERBOSE_LOGGING */
