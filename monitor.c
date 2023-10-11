#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "error.h"
#include "monitor.h"

static void release_child_resources(monitor_t *m) {}

static void release_parent_resources(monitor_t *m, error_t *err) {
	for (int fd = 3; fd < getdtablesize(); fd++) {
		if (close(fd) != -1) {
			continue;
		}

		err->message = strerror(errno);
		return;
	}
}

static size_t find_pid_index(monitor_t *m, int pid) {
	for (size_t i = 0; i < m->pids_count; i++) {
		pid_t pid2 = m->pids[i];
		if (pid2 == pid) {
			return i;
		}
	}

	return m->pids_count;
}

static void monitor_wait(monitor_t *m) {
	int exit_code;

	while (!m->should_shutdown) {
		int pid = waitpid(-1, &exit_code, 0);
		size_t index = find_pid_index(m, pid);

		if (index >= m->pids_count) {
			continue;
		}

		// TODO: update state here
		printf("process with pid %d crashed with exit code %d\n", pid, exit_code);
	}
}

void monitor_init(monitor_t *m) {
	m->pid = -1;
	m->should_shutdown = false;

	m->pids_count = 0;
}

// TODO: should only be called through IPC
void monitor_add_service(monitor_t *m, pid_t pid) {
	m->pids[m->pids_count++] = pid;
}

// TODO: make this faster
// TODO: should only be called through IPC
bool monitor_remove_service(monitor_t *m, pid_t pid) {
	size_t index = find_pid_index(m, pid);

	if (index >= m->pids_count) {
		return false;
	}

	m->pids_count--;

	// TODO: refactor to splice function
	for (size_t i = index; i < m->pids_count; ++i) {
		m->pids[i] = m->pids[i + 1];
	}

	return true;
}

void monitor_start(monitor_t *m, error_t *err) {
	m->pid = fork();

	if (m->pid < 0) {
		err->message = "starting monitoring failed";
		return;
	}

	bool is_parent_service = m->pid != 0;

	if (is_parent_service) {
		release_child_resources(m);
	} else {
		release_parent_resources(m, err);

		if (error_exist(err)) {
			error_print(err);
			exit(1);
		}

		monitor_wait(m);
	}
}

// TODO: implement this
void monitor_stop(monitor_t *m, error_t *err) {}
