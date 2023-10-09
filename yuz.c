#include <stdlib.h>

#include "process.h"
#include "yuz.h"

void yuz_init(yuz_t *yuz) {
	yuz->process_count = 0;
	// TODO: make this dynamic
	yuz->processes = malloc(sizeof(process_t) * MAX_PROCESSES);
	for (int i = 0; i < MAX_PROCESSES; ++i) {
		process_t *proc = yuz->processes + i;
		yuz_process_init(yuz, proc);
	}
}

void yuz_process_init(yuz_t *yuz, process_t *p) {
	p->index = yuz->process_count++;
}
