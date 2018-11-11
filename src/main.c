#include <stdio.h>

#include "env.h"
#include "state.h"
#include "window.h"

int main(int argc, char **argv) {
    struct env_t *env = createEnvironment();


    /*
      Kansai is effectively a state machine operating on a
      series of scenes.
      
      state_t contains a function pointer to an arbitrary 
      `update' function that takes in a pointer to the current 
      state, a pointer to the env so that it can do drawing 
      and such, and flags (which are different for each state).

      Each scene has an initialization function that will
      populate the structure and then return it with all the
      info (entities) it'll need.
     */

    /* populate the state pointer with the initial state */
    struct state_t *state = startGame();
    
    int game_running = 1;
    while (game_running) {
        /* update the current state */
        state->update(env, state);
        clearWindow(env);
    }
}
