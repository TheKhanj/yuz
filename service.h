#ifndef SERVICE__H
#define SERVICE__H

#include "error.h"
#include <sys/types.h>

enum state_t { PS_SHUTDOWN = 0, PS_STARTED, PS_LOADED, PS_READY, PS_CRASHED };

typedef struct service_t service_t;

typedef void (*service_load)(service_t *p);
typedef void (*service_stop)(service_t *p);
typedef void (*service_start)(service_t *p);
typedef void (*service_prepare)(service_t *p);
typedef void (*service_force_stop)(service_t *p);

typedef struct service_methods_t {
	service_start start;
	service_load load;
	service_prepare prepare;
	service_stop stop;
	service_force_stop force_stop;
} service_methods_t;

struct service_t {
	// TODO: not needed
	uint id;
	pid_t pid;

	enum state_t state;

	int stdin_fd, stdout_fd, stderr_fd;

	char *command;
	char **args;

	service_methods_t methods;
};

void service_exec(service_t *p, error_t *err);

#endif // SERVICE__H
