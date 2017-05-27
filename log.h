#ifndef __LOG_H
#define __LOG_H

#include <stdlib.h>

#if defined _LOG_MIN_TRACE
#define LOG_LEVEL 0
#elif defined _LOG_MIN_DEBUG
#define LOG_LEVEL 1
#elif defined _LOG_MIN_INFO
#define LOG_LEVEL 2
#elif defined _LOG_MIN_WARN
#define LOG_LEVEL 3
#elif defined _LOG_MIN_ERROR
#define LOG_LEVEL 4
#elif defined _LOG_MIN_FATAL
#define LOG_LEVEL 5
#else
#define LOG_LEVEL 2
#endif

#define LOG_PREFIX_TRACE "[" "\x1B[97m" "TRACE" "\x1B[0m" "]"
#define LOG_PREFIX_DEBUG "[" "\x1B[96m" "DEBUG" "\x1B[0m" "]"
#define LOG_PREFIX_INFO  "[" "\x1B[92m" " INFO" "\x1B[0m" "]"
#define LOG_PREFIX_WARN  "[" "\x1B[93m" " WARN" "\x1B[0m" "]"
#define LOG_PREFIX_ERROR "[" "\x1B[91m" "ERROR" "\x1B[0m" "]"
#define LOG_PREFIX_FATAL "[" "\x1B[95m" "FATAL" "\x1B[0m" "]"

#if LOG_LEVEL <= 0
#define log_trace(fmt, ...) \
	log_(LOG_PREFIX_TRACE " " __FILE__, sizeof(LOG_PREFIX_TRACE " " __FILE__), \
		":%d " fmt, __LINE__, ##__VA_ARGS__)
#else
#define log_trace(fmt, ...)
#endif

#if LOG_LEVEL <= 1
#define log_debug(fmt, ...) \
	log_(LOG_PREFIX_DEBUG " " __FILE__, sizeof(LOG_PREFIX_DEBUG " " __FILE__), \
		":%d " fmt, __LINE__, ##__VA_ARGS__)
#else
#define log_debug(fmt, ...)
#endif

#if LOG_LEVEL <= 2
#define log_info(fmt, ...) \
	log_(LOG_PREFIX_INFO " ", sizeof(LOG_PREFIX_INFO " "), fmt, ##__VA_ARGS__)
#else
#define log_info(fmt, ...)
#endif

#if LOG_LEVEL <= 3
#define log_warn(fmt, ...) \
	log_(LOG_PREFIX_WARN " ", sizeof(LOG_PREFIX_WARN " "), fmt, ##__VA_ARGS__)
#else
#define log_warn(fmt, ...)
#endif

#if LOG_LEVEL <= 4
#include <string.h>
#include <errno.h>
#define log_error(fmt, ...) \
	log_(LOG_PREFIX_ERROR " " __FILE__, sizeof(LOG_PREFIX_ERROR " " __FILE__), \
		":%d " fmt, __LINE__, ##__VA_ARGS__)
#define log_perror(fmt, ...) \
	log_(LOG_PREFIX_ERROR " " __FILE__, sizeof(LOG_PREFIX_ERROR " " __FILE__), \
		":%d " fmt ": %s", __LINE__, ##__VA_ARGS__, strerror(errno))
#else
#define log_error(fmt, ...)
#define log_perror(fmt, ...)
#endif

#if LOG_LEVEL <= 5
#define log_fatal(fmt, ...) \
	log_(LOG_PREFIX_FATAL " " __FILE__, sizeof(LOG_PREFIX_FATAL " " __FILE__), \
		":%d " fmt, __LINE__, ##__VA_ARGS__)
#else
#define log_fatal(fmt, ...)
#endif


int log_set_logfile(const char *filepath);
int log_unset_logfile(void);
void log_(const char *prefix, size_t prefix_size, const char *fmt, ...);

#endif
