#include "process.h"

typedef struct {
	process_t *p;
} monitor_t;

void monitor_start(monitor_t *m);
void monitor_stop(monitor_t *m);
