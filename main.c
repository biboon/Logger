#include "log.h"

int main(int argc, char *argv[])
{
	log_start(NULL);
	log_all("all");
	log_trace("trace");
	log_debug("debug");
	log_info("info");
	log_warn("warn");
	log_error("error");
	log_perror("perror");
	log_fatal("fatal");
	log_end();
	return 0;
}
