#include "log.h"

#ifndef _LOG_DISABLE

#include <stdarg.h>
#include <time.h>


#ifndef _LOG_LEVEL
#define _LOG_LEVEL LOG_INFO
#endif /* _LOG_LEVEL */

#ifndef _LOG_NO_FORMATTING

#define RESET "\033[0m"
static const char * const prefix[] = {
	[LOG_TRACE ] = "\033[36m",
	[LOG_DEBUG ] = "\033[34m",
	[LOG_NORMAL] = "\033[37m",
	[LOG_INFO  ] = "\033[32m",
	[LOG_WARN  ] = "\033[33m",
	[LOG_ERROR ] = "\033[31m",
	[LOG_FATAL ] = "\033[31m\033[1m",
};

#else

#define RESET
static const char * const prefix[] = {
	[LOG_TRACE]  = "trace ",
	[LOG_DEBUG]  = "debug ",
	[LOG_NORMAL] = "      ",
	[LOG_INFO]   = "info  ",
	[LOG_WARN]   = "warn  ",
	[LOG_ERROR]  = "error ",
	[LOG_FATAL]  = "fatal ",
};

#endif /* _LOG_NO_FORMATTING */


void flog_(FILE *stream, enum log_level level, const char *fmt, ...)
{
	char date[18], msg[160];
	time_t tloc;
	struct tm *time_info;
	va_list arg;

	if (level < _LOG_LEVEL) return;

	tloc = time(NULL);
	time_info = localtime(&tloc);
	strftime(date, sizeof date, "%y-%m-%d %H:%M:%S", time_info);

	va_start(arg, fmt);
	vsnprintf(msg, sizeof msg, fmt, arg);
	va_end(arg);

	fprintf(stream, "[%17s] %s%s" RESET "\n", date, prefix[level], msg);
}

#endif /* _LOG_DISABLE */
