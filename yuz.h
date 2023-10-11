#ifndef YUZ__H
#define YUZ__H

#include "service.h"
#include <stddef.h>
#include <sys/types.h>

typedef struct yuz_t {
	size_t service_count;
	// TODO: make this dynamic
	service_t services[256];
} yuz_t;

void yuz_init(yuz_t *yuz);
void yuz_service_init(yuz_t *yuz, service_t *p);

#endif // YUZ__H
