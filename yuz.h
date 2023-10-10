#ifndef YUZ__H
#define YUZ__H

#include "process.h"
#include <sys/types.h>

typedef struct yuz_t {
	uint process_count;
	// TODO: make this dynamic
	process_t processes[256];
} yuz_t;

void yuz_init(yuz_t *yuz);
void yuz_process_init(yuz_t *yuz, process_t *p);

#endif // YUZ__H
