#include <stdbool.h>
#include <stddef.h>
#include <sys/wait.h>
#include <unistd.h>

#include "error.h"
#include "monitor.h"
#include "process.h"

static void monitor_listen(monitor_t *m) {
	int exit_code;

	while (true) {
		int pid = waitpid(-1, &exit_code, 0);
	}
}

static void monitor_release_child_resources(monitor_t *m) {}

static void monitor_release_parent_resources(monitor_t *m) {}

static size_t monitor_find_process_index(monitor_t *m, int pid) {
	for (size_t i = 0; i < m->process_count; i++) {
		process_t *p2 = m->processes[i];
		if (p2->id == pid) {
			return i;
		}
	}

	return m->process_count;
}

void monitor_init(monitor_t *m) {
	m->pid = -1;
	m->process_count = 0;
}

void monitor_add_process(monitor_t *m, process_t *p) {
	m->processes[m->process_count++] = p;
}

// TODO: make this faster
bool monitor_remove_process(monitor_t *m, process_t *p) {
	size_t index = monitor_find_process_index(m, p->id);

	if (index >= m->process_count) {
		return false;
	}

	m->process_count--;

	// TODO: refactor to splice function
	for (size_t i = index; i < m->process_count; ++i) {
		m->processes[i] = m->processes[i + 1];
	}

	return true;
}

void monitor_start(monitor_t *m, error_t *err) {
	m->pid = fork();

	if (m->pid < 0) {
		err->message = "starting monitoring failed";
		return;
	}

	bool is_parent_process = m->pid != 0;

	if (is_parent_process) {
		monitor_release_child_resources(m);

	} else {
		monitor_release_parent_resources(m);
		monitor_listen(m);
	}
}

// TODO: implement this
void monitor_stop(monitor_t *m, error_t *err) {}
