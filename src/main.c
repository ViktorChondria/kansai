#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "bytecode.h"

int main(int argc, char **argv) {
    script_t *env = initEnv();
    uint8_t test[] = {00, 00, 00, 00, 04, 03, 00, 00, 00, 00, 00, 01};
    env = loadScript(env, test, 6);
    executeScript(env);
    return 0;
}
