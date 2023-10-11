#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "error.h"
#include "service.h"

void test_something() {
	char *args[] = {"/usr/bin/sleep", "1", NULL};

	service_t p = {
			.id = 1,
			.pid = -1,
			.state = PS_SHUTDOWN,
			.command = "/usr/bin/sleep",
			.stdin_fd = 0,
			.stdout_fd = 1,
			.stderr_fd = 2,
			.args = args,
	};

	error_t err;
	error_reset(&err);
	service_exec(&p, &err);
	int exit_code;
	close(0);
	close(1);
	close(2);
	printf("hello world\n");
	int pid = waitpid(-1, &exit_code, 0);

	// kill(p.pid, SIGTERM);
	exit(123);
}

int main() { test_something(); }
