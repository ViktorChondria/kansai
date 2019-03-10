#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "log.h"

void fatal(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

void debug(char *fmt, ...) {
#ifdef _DEBUG
    va_list args;
    va_start(args, fmt);
    /* no newline, print before message. */
    printf("[DEBUG] ");
    vprintf(fmt, args);
    printf("\n");
    va_end(args);
#endif
}
