#ifndef SERVICE__H
#define SERVICE__H

#include "error.h"
#include <sys/types.h>

enum state_t { PS_SHUTDOWN = 0, PS_STARTED, PS_LOADED, PS_READY, PS_CRASHED };

typedef struct service_t service_t;

struct service_t {
	pid_t pid;

	enum state_t state;

	int stdin_fd, stdout_fd, stderr_fd;

	char *command;
	char **args;
};

void service_exec(service_t *p, error_t *err);

#endif // SERVICE__H
