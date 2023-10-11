#ifndef MONITOR__H
#define MONITOR__H

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

#include "error.h"
#include "service.h"

typedef struct {
	pid_t pid;
	bool should_shutdown;

	size_t pids_count;
	// TODO: make this dynamic
	pid_t pids[256];
} monitor_t;

void monitor_init(monitor_t *m);
void monitor_stop(monitor_t *m, error_t *err);
void monitor_start(monitor_t *m, error_t *err);
// TODO: should only be called through IPC
void monitor_add_service(monitor_t *m, pid_t pid);
// TODO: should only be called through IPC
bool monitor_remove_service(monitor_t *m, pid_t pid);

#endif // MONITOR__H
