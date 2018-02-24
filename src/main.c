#include "log.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


static void bench(FILE *stream, unsigned loops)
{
	struct timeval start = { 0 };
	struct timeval stop = { 0 };

	gettimeofday(&start, NULL);

	for (unsigned i = loops ; i > 0; --i)
		flog_error(stream, "Zobzob");

	gettimeofday(&stop, NULL);

	long int micros = (stop.tv_sec - start.tv_sec) * 1000000 +
		stop.tv_usec - start.tv_usec;

	printf("Time elapsed: %.6f seconds\n", (float)micros / 1e6);
	printf("Logs per second: %.6f\n", (float)loops * 1e6 / (float)micros);
	printf("Time per log: %.6f us\n", (float)micros / (float)loops);
}


int main(int argc, char *argv[])
{
	log_trace("This is a trace logging message");
	log_debug("This is a debug logging message");
	log("This is a logging message");
	log_info("This is a info logging message");
	log_warn("This is a warn logging message");
	log_error("This is a error logging message");
	log_perror("This is a perror logging message");
	log_fatal("This is a fatal logging message");

	if (argc >= 2)
	{
		FILE *stream = fopen("out.txt", "w");
		bench(stream, (unsigned) strtoul(argv[1], NULL, 0));
		fclose(stream);
	}

	return 0;
}
