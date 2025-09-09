#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void panic(const char *message, int error) {
  fprintf(stderr, "[%d]: %s\n", error, message);
  exit(error);
}
