#include "log.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


static void bench(unsigned loops)
{
	struct timeval start = { 0 };
	struct timeval stop = { 0 };

	gettimeofday(&start, NULL);
	for (unsigned i = loops ; i > 0; --i) {
		log_error("Zobzob");
	}
	gettimeofday(&stop, NULL);
	long int micros = (stop.tv_sec - start.tv_sec) * 1000000 +
		stop.tv_usec - start.tv_usec;

	printf("Time elapsed: %.6f seconds\n", (float)micros / 1e6);
	printf("Logs per second: %.6f\n", (float)loops * 1e6 / (float)micros);
}


int main(int argc, char *argv[])
{
	if (argc < 2)
		return -1;
	else if (argc < 3)
		log_start(NULL);
	else
		log_start(argv[2]);

	log_all("all");
	log_trace("trace");
	log_debug("debug");
	log_info("info");
	log_warn("warn");
	log_error("error");
	log_fatal("fatal");

	bench((unsigned) strtoul(argv[1], NULL, 0));

	log_end();
	
	return 0;
}
