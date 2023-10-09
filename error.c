#include <stdbool.h>
#include <stddef.h>

#include "error.h"

void error_reset(error_t *err) { err->message = NULL; }

bool error_exist(error_t *err) { return err->message != NULL; }

void error_message(error_t *err, char *message) { err->message = message; }
