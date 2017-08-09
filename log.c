#include "log.h"

#ifndef _LOG_DISABLE

#include <stdio.h>
#include <stdarg.h>
#include <time.h>


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

static const enum log_level threshold = _LOG_LEVEL;
static FILE *output;


int log_start(const char *filepath)
{
	output = filepath != NULL ? fopen(filepath, "ae") : stdout;
	return output != NULL ? 0 : -1;
}

void log_(enum log_level level, const char * restrict fmt, ...)
{
	if (level < threshold) return;

	char date[18], msg[160];
	time_t tloc = time(NULL);
	struct tm *time_info = localtime(&tloc);
	strftime(date, sizeof date, "%y-%m-%d %H:%M:%S", time_info);

	va_list arg;
	va_start(arg, fmt);
	vsnprintf(msg, sizeof msg, fmt, arg);
	va_end(arg);

	fprintf(output, "(%17s %s) %s\n", date, level_str[level], msg);
}

void log_end(void)
{
	if (output != NULL && output != stdout) fclose(output);
}

#else

int log_start(const char *filepath)
{
	(void) filepath;
	return 0;
}

#endif /* _LOG_DISABLE */
