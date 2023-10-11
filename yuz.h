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

#endif // YUZ__H
