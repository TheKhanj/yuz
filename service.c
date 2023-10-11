#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "error.h"
#include "service.h"

static void service_set_state(service_t *p, enum state_t state) {
	p->state = state;
}

static void service_release_parent_resources(service_t *p, error_t *err) {
	for (int fd = 3; fd < getdtablesize(); fd++) {
		if (fd == p->stdin_fd || fd == p->stdout_fd || fd == p->stderr_fd) {
			continue;
		}

		if (close(fd) == -1) {
			continue;
		}

		err->message = strerror(errno);

		if (error_exist(err)) {
			return;
		}
	}
}

static void service_redirect_std_streams(service_t *p, error_t *err) {
	const int fds[] = {p->stdin_fd, p->stdout_fd, p->stderr_fd};

	for (int i = 0; i < 3; i++) {
		int fd = fds[i];
		if (dup2(fd, i) == -1) {
			err->message = strerror(errno);

			return;
		}
	}
}

void service_exec(service_t *p, error_t *err) {
	pid_t pid;
	pid = fork();

	if (pid < 0) {
		service_set_state(p, PS_CRASHED);
		return;
	}

	bool is_parent_service = pid != 0;

	if (is_parent_service) {
		service_set_state(p, PS_STARTED);
		p->pid = pid;

		return;
	}

	service_redirect_std_streams(p, err);

	if (error_exist(err)) {
		error_print(err);
		exit(1);
	}

	service_release_parent_resources(p, err);

	if (error_exist(err)) {
		error_print(err);
		exit(1);
	}

	if (execv(p->command, p->args) == -1) {
		exit(1);
	}

	exit(0);
}
