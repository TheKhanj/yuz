#ifndef MONITOR__H
#define MONITOR__H

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

#include "error.h"
#include "service.h"

typedef struct {
	pid_t pid;
	size_t service_count;
	// TODO: make this dynamic
	service_t *services[256];
} monitor_t;

void monitor_init(monitor_t *m);
void monitor_add_service(monitor_t *m, service_t *p);
bool monitor_remove_service(monitor_t *m, service_t *p);
void monitor_start(monitor_t *m, error_t *err);
void monitor_stop(monitor_t *m, error_t *err);

#endif // MONITOR__H
