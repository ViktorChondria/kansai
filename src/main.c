#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "bytecode.h"

int main(int argc, char **argv) {
    script_t *env = initEnv();
    uint8_t test[] = {0x00, 0x00, 0x00, 0x00, 0x04, 0x03, 0x00, 0x10, 0x00, 0x02, 0x00, 0x01};
    env = loadScript(env, test, 12);
    executeScript(env);
    return 0;
}
