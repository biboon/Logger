#ifndef __LOG_H
#define __LOG_H

#include <stdio.h>
#include <string.h>
#include <errno.h>


#define flog_trace(stream, ...)  flog_(stream, LOG_TRACE , __VA_ARGS__)
#define flog_debug(stream, ...)  flog_(stream, LOG_DEBUG , __VA_ARGS__)
#define flog(stream, ...)        flog_(stream, LOG_NORMAL, __VA_ARGS__)
#define flog_info(stream, ...)   flog_(stream, LOG_INFO  , __VA_ARGS__)
#define flog_warn(stream, ...)   flog_(stream, LOG_WARN  , __VA_ARGS__)
#define flog_error(stream, ...)  flog_(stream, LOG_ERROR , __VA_ARGS__)
#define flog_fatal(stream, ...)  flog_(stream, LOG_FATAL , __VA_ARGS__)
#define flog_perror(stream, str) flog_(stream, LOG_ERROR , str ": %s", strerror(errno))

#define log_trace(...)  flog_trace(stdout, __VA_ARGS__)
#define log_debug(...)  flog_debug(stdout, __VA_ARGS__)
#define log(...)        flog(stdout, __VA_ARGS__)
#define log_info(...)   flog_info(stdout, __VA_ARGS__)
#define log_warn(...)   flog_warn(stdout, __VA_ARGS__)
#define log_error(...)  flog_error(stdout, __VA_ARGS__)
#define log_fatal(...)  flog_fatal(stdout, __VA_ARGS__)
#define log_perror(str) flog_perror(stdout, str)


#ifndef _LOG_DISABLE

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum log_level {
	LOG_TRACE, LOG_DEBUG, LOG_NORMAL, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL
};

void flog_(FILE *stream, enum log_level level, const char *fmt, ...);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#else

#define flog_(stream, level, fmt, ...) ((void) 0)

#endif /* _LOG_DISABLE */


#endif /* __LOG_H */
