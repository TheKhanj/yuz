#ifndef PROCESS__H
#define PROCESS__H
#include <sys/types.h>

enum state_t { PS_SHUTDOWN = 0, PS_STARTED, PS_LOADED, PS_READY, PS_CRASHED };

typedef struct process_t process_t;

typedef void (*process_start)(process_t *p);
typedef void (*process_load)(process_t *p);
typedef void (*process_prepare)(process_t *p);
typedef void (*process_stop)(process_t *p);
typedef void (*process_force_stop)(process_t *p);

typedef struct process_methods_t {
	process_start start;
	process_load load;
	process_prepare prepare;
	process_stop stop;
	process_force_stop force_stop;
} process_methods_t;

struct process_t {
	uint index;

	enum state_t state;
	char *command;
	pid_t pid;

	process_methods_t methods;
};

#endif // PROCESS__H
