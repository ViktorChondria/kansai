#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "bytecode.h"

int main(int argc, char **argv) {
    script_t *env = initEnv();
    uint8_t test[] = {0, 0, 0, 0, 0, 0, 0, 1};
    env = loadScript(env, test, 8);
    executeScript(env);
    return 0;
}
