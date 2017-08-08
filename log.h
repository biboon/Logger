#ifndef __LOG_H
#define __LOG_H

#define LOG_ALL   0
#define LOG_TRACE 1
#define LOG_DEBUG 2
#define LOG_INFO  3
#define LOG_WARN  4
#define LOG_ERROR 5
#define LOG_FATAL 6

#if !defined(_LOG_DISABLE)
# ifndef _LOG_LEVEL
#  define _LOG_LEVEL LOG_INFO
# else
#  if _LOG_LEVEL > LOG_FATAL || _LOG_LEVEL < LOG_ALL
#   error "Invalid value for _LOG_LEVEL"
#  endif
# endif
#endif


#if !defined(_LOG_DISABLE) && _LOG_LEVEL <= LOG_ALL
# define log_all(...) log_(LOG_ALL, __VA_ARGS__)
#else
# define log_all(...) (void) 0
#endif

#if !defined(_LOG_DISABLE) && _LOG_LEVEL <= LOG_TRACE
# define log_trace(...) log_(LOG_TRACE, __VA_ARGS__)
#else
# define log_trace(...) (void) 0
#endif

#if !defined(_LOG_DISABLE) && _LOG_LEVEL <= LOG_DEBUG
# define log_debug(...) log_(LOG_DEBUG, __VA_ARGS__)
#else
# define log_debug(...) (void) 0
#endif

#if !defined(_LOG_DISABLE) && _LOG_LEVEL <= LOG_INFO
# define log_info(...) log_(LOG_INFO, __VA_ARGS__)
#else
# define log_info(...) (void) 0
#endif

#if !defined(_LOG_DISABLE) && _LOG_LEVEL <= LOG_WARN
# define log_warn(...) log_(LOG_WARN, __VA_ARGS__)
#else
# define log_warn(...) (void) 0
#endif

#if !defined(_LOG_DISABLE) && _LOG_LEVEL <= LOG_ERROR
# define log_error(...) log_(LOG_ERROR, __VA_ARGS__)
#else
# define log_error(...) (void) 0
#endif

#if !defined(_LOG_DISABLE) && _LOG_LEVEL <= LOG_FATAL
# define log_fatal(...) log_(LOG_FATAL, __VA_ARGS__)
#else
# define log_fatal(...) (void) 0
#endif


#ifdef __cplusplus
extern "C" {
#endif

int log_start(const char *filepath);
int log_end(void);
void log_(int level, const char * restrict fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
