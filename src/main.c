#include <stdio.h>

#include "env.h"
#include "state.h"
#include "window.h"
#include "archive.h"

int main(int argc, char **argv) {

    env_t *env = createEnvironment();
    int game_running = 1;
    while (game_running) {
        /* update the current state */
        //state->update(env, state);
        clearWindow(env);
    }
}
