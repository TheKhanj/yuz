#include <stddef.h>
#include <stdlib.h>

#include "error.h"
#include "service.h"
#include "yuz.h"

// TODO: use dfs algorithm
void yuz_start(yuz_t *yuz) {
	error_t err;
	error_reset(&err);

	for (size_t i = 0; i < yuz->service_count; ++i) {
		service_t *s = yuz->services + i;
		service_exec(s, &err);

		if (error_exist(&err)) {
			error_print(&err);
			exit(1);
		}
	}
}
