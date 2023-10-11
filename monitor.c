#include <stdbool.h>
#include <stddef.h>
#include <sys/wait.h>
#include <unistd.h>

#include "error.h"
#include "monitor.h"
#include "service.h"

static void monitor_listen(monitor_t *m) {
	int exit_code;

	while (true) {
		int pid = waitpid(-1, &exit_code, 0);
	}
}

static void monitor_release_child_resources(monitor_t *m) {}

static void monitor_release_parent_resources(monitor_t *m) {}

static size_t monitor_find_service_index(monitor_t *m, int pid) {
	for (size_t i = 0; i < m->service_count; i++) {
		service_t *p2 = m->services[i];
		if (p2->pid == pid) {
			return i;
		}
	}

	return m->service_count;
}

void monitor_init(monitor_t *m) {
	m->pid = -1;
	m->service_count = 0;
}

void monitor_add_service(monitor_t *m, service_t *p) {
	m->services[m->service_count++] = p;
}

// TODO: make this faster
bool monitor_remove_service(monitor_t *m, service_t *p) {
	size_t index = monitor_find_service_index(m, p->pid);

	if (index >= m->service_count) {
		return false;
	}

	m->service_count--;

	// TODO: refactor to splice function
	for (size_t i = index; i < m->service_count; ++i) {
		m->services[i] = m->services[i + 1];
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
		monitor_release_child_resources(m);
	} else {
		monitor_release_parent_resources(m);
		monitor_listen(m);
	}
}

// TODO: implement this
void monitor_stop(monitor_t *m, error_t *err) {}
