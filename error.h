#ifndef ERROR__H
#define ERROR__H

#include <stdbool.h>

typedef struct error_t {
	char *message;
} error_t;

void error_reset(error_t *err);
bool error_exist(error_t *err);

#endif // ERROR__H
