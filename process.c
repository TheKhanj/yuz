#include <unistd.h>

#include "process.h"

void process_set_state(process_t *p, enum state_t state) { p->state = state; }

// TODO: deallocate file descriptor
void process_start_fork(process_t *p) {
	p->pid = fork();

	if (p->pid < 0) {
		process_set_state(p, PS_CRASHED);
		return;
	}

	process_set_state(p, PS_STARTED);

	int pipe[2][2];
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			pipe[i][j] = -1;

	if (pipe(pipe[0]) == -1 || pipe(pipe[1]) == -1) {
		goto defer;
	}

	if (p->pid != 0) {
		return;
	}

	return;

defer:
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++) {
			int fd = pipe[i][j];
			if (fd != -1) {
				close(fd);
			}
		}
}
