#include "log.h"

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#ifdef __GNUC__
#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)
#else
#define likely(x)       (x)
#define unlikely(x)     (x)
#endif


static const char * const level_str[] = {
#ifndef _LOG_NO_COLOR
	[LOG_ALL]   = "\033[37m" "  all" "\033[0m",
	[LOG_TRACE] = "\033[36m" "trace" "\033[0m",
	[LOG_DEBUG] = "\033[34m" "debug" "\033[0m",
	[LOG_INFO]  = "\033[32m" " info" "\033[0m",
	[LOG_WARN]  = "\033[33m" " warn" "\033[0m",
	[LOG_ERROR] = "\033[31m" "error" "\033[0m",
	[LOG_FATAL] = "\033[35m" "fatal" "\033[0m",
#else
	[LOG_ALL]   = "  all",
	[LOG_TRACE] = "trace",
	[LOG_DEBUG] = "debug",
	[LOG_INFO]  = " info",
	[LOG_WARN]  = " warn",
	[LOG_ERROR] = "error",
	[LOG_FATAL] = "fatal",
#endif
};

static FILE *output;


int log_start(const char *filepath)
{
	output = filepath != NULL ? fopen(filepath, "ae") : stdout;
	return output != NULL ? 0 : -1;
}

int log_end(void)
{
	return output != NULL ? fclose(output) : 0;
}


void log_(int level, const char * restrict fmt, ...)
{
	char date[18], msg[160];
	time_t tloc = time(NULL);
	struct tm *time_info = localtime(&tloc);
	if (unlikely(strftime(date, sizeof date, "%y-%m-%d %H:%M:%S", time_info) == 0))
		return;
	va_list arg;
	va_start(arg, fmt);
	if (unlikely(vsnprintf(msg, sizeof msg, fmt, arg) < 0))
		return;
	va_end(arg);
	fprintf(output, "(%17s %s) %s\n", date, level_str[level], msg);
}
