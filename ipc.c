#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

#include "error.h"
#include "process.h"
#include "yuz.h"

typedef struct {
	int readable_fd;
	int writable_fd;
} pipe_t;

void pipe_allocate(pipe_t *p, error_t *err) {
	int pipes[2];

	if (pipe(pipes) == -1) {
		err->message = strerror(errno);
		return;
	}

	p->readable_fd = pipes[0];
	p->writable_fd = pipes[1];
}

void pipe_deallocate(pipe_t *p, error_t *err) {
	if (close(p->readable_fd) == -1 || close(p->writable_fd) == -1) {
		err->message = strerror(errno);
	}
}

typedef struct {
	yuz_t *yuz;
	pipe_t pipes[MAX_PROCESSES][2];
} ipc_t;

void ipc_deallocate(ipc_t *ipc, uint proc_index, error_t *err) {
	pipe_t(*p)[2] = ipc->pipes + proc_index;

	pipe_deallocate(p[0], err);
	pipe_deallocate(p[1], err);
}

void ipc_allocate(ipc_t *ipc, uint proc_index, error_t *err) {
	pipe_t(*p)[2] = ipc->pipes + proc_index;

	pipe_allocate(p[0], err);
	if (error_exist(err)) {
		ipc_deallocate(ipc, proc_index, err);
		return;
	}
	pipe_allocate(p[1], err);
	if (error_exist(err)) {
		ipc_deallocate(ipc, proc_index, err);
		return;
	}

	return;
}

void ipc_get_read_fd(ipc_t *ipc, uint proc_index) {
	pipe_t(*p)[2] = ipc->pipes + proc_index;
}
