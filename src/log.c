#include <stdio.h>
#include <stdlib.h>
#include "log.h"

void fatal(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}
