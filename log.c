#include "log.h"

#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#if defined _REENTRANT || defined _THREAD_SAFE
#include <pthread.h>
#define log_lock()   pthread_mutex_lock(&lock)
#define log_unlock() pthread_mutex_unlock(&lock)
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
#else
#define log_lock()
#define log_unlock()
#endif

#ifdef __GNUC__
#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)
#else
#define likely(x)       (x)
#define unlikely(x)     (x)
#endif


static int fd = STDOUT_FILENO; // Write to stdout by default


int log_set_logfile(const char *filepath)
{
	if (filepath == NULL) return -1;
	int _fd = open(filepath,
		O_WRONLY | O_APPEND | O_CREAT | O_CLOEXEC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
	);
	if (_fd == -1) return -1;
	log_lock();
	fd = _fd;
	log_unlock();
	return 0;
}


int log_unset_logfile(void)
{
	int status = -1;
	log_lock();
	if (fd != STDOUT_FILENO) {
		status = close(fd);
		fd = STDOUT_FILENO;
	}
	log_unlock();
	return status;
}


void log_(const char *prefix, size_t prefix_size, const char *fmt, ...)
{
	time_t tloc = time(NULL);
	struct tm *time_info = localtime(&tloc);
	char line[256];
	size_t bytes = strftime(line, 19, "%y-%m-%d %H:%M:%S ", time_info);
	if (unlikely(bytes != 18)) return;
	memcpy(line + bytes, prefix, prefix_size);
	bytes += prefix_size;
	va_list arg;
	va_start(arg, fmt);
	int written = vsnprintf(line + bytes, sizeof line - bytes, fmt, arg);
	va_end(arg);
	if (unlikely(written < 0)) return;
	bytes += written;
	if (unlikely(bytes >= sizeof line)) bytes = sizeof line - 1;
	line[bytes++] = '\n';
	char *lptr = &line[0];
	log_lock();
	do {
		ssize_t size = write(fd, lptr, bytes);
		if (unlikely(size < 0)) break;
		lptr += size;
		bytes -= size;
	} while (bytes > 0);
	log_unlock();
}
