#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "graphics.h"

int main(int argc, char **argv) {
    setupWindow();
    clearWindow();
    updateWindow();

    clearSDL();
    return 0;
}
