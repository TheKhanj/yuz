#include <stdlib.h>

#include "process.h"
#include "yuz.h"

void yuz_init(yuz_t *yuz) {
	yuz->process_count = 0;
	// TODO: make this dynamic
	yuz->processes = malloc(sizeof(process_t) * MAX_PROCESSES);
}

void yuz_add_process(yuz_t *yuz) {
	p->id = yuz->process_count++;
}
