#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "error.h"
#include "process.h"

void process_send_state(process_t *p, enum state_t state) {}

void process_set_state(process_t *p, enum state_t state) {
	p->state = state;
	process_send_state(p, state);
}

static void release_parent_resources(process_t *p, error_t *err) {
	for (int fd = 3; fd < getdtablesize(); fd++) {
		if (fd != p->recv_fd && fd != p->send_fd) {
			if (close(fd) != -1) {
				error_message(err, strerror(errno));
				if (error_exist(err)) {
					return;
				}
			}
		}
	}
}

static void release_child_resources(process_t *p, error_t *err) {
	if (close(p->recv_fd) == -1 || close(p->send_fd) == -1) {
		error_message(err, strerror(errno));
	}
}

void process_fork(process_t *p, void (*child_action)(process_t *p),
									error_t *err) {
	p->pid = fork();

	if (p->pid < 0) {
		process_send_state(p, PS_CRASHED);
		return;
	}

	process_set_state(p, PS_STARTED);

	if (p->pid != 0) {
		release_child_resources(p, err);
		return;
	}

	release_parent_resources(p, err);
	if (error_exist(err)) {
		return;
	}

	child_action(p);
}

void process_listen(process_t *p) {}
