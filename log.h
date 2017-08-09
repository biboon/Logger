#ifndef __LOG_H
#define __LOG_H
#ifndef _LOG_DISABLE

#include <string.h>
#include <errno.h>

enum log_level {
	LOG_ALL, LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL
};

#ifndef _LOG_LEVEL
#define _LOG_LEVEL LOG_INFO
#endif

#define log_all(...)    log_(LOG_ALL, __VA_ARGS__)
#define log_trace(...)  log_(LOG_TRACE, __VA_ARGS__)
#define log_debug(...)  log_(LOG_DEBUG, __VA_ARGS__)
#define log_info(...)   log_(LOG_INFO, __VA_ARGS__)
#define log_warn(...)   log_(LOG_WARN, __VA_ARGS__)
#define log_error(...)  log_(LOG_ERROR, __VA_ARGS__)
#define log_fatal(...)  log_(LOG_FATAL, __VA_ARGS__)
#define log_perror(fmt) log_(LOG_ERROR, fmt ": %s", strerror(errno))

#ifdef __cplusplus
extern "C" {
#endif
int log_start(const char *filepath);
int log_end(void);
void log_(enum log_level level, const char * restrict fmt, ...);
#ifdef __cplusplus
}
#endif

#else

#define log_all(...)    (void) 0
#define log_trace(...)  (void) 0
#define log_debug(...)  (void) 0
#define log_info(...)   (void) 0
#define log_warn(...)   (void) 0
#define log_error(...)  (void) 0
#define log_fatal(...)  (void) 0
#define log_perror(fmt) (void) 0
#define log_start(...)  (void) 0
#define log_end(...)    (void) 0
#define log_(...)       (void) 0

#endif /* _LOG_DISABLE */
#endif /* __LOG_H */
