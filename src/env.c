#include <stdlib.h>
#include "window.h"
#include "env.h"
#include "log.h"


struct env_t *createEnvironment() {
    struct env_t *env = malloc(sizeof(struct env_t));
    
    env->surface = NULL;
    env->window = NULL;

    /* initialize the shared resources */
    env->window = SDL_CreateWindow("Kansai",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   WIDTH,
                                   HEIGHT,
                                   SDL_WINDOW_SHOWN);
    if (!env->window) {
        fatal("Could not initialize window.");
    }

    env->surface = SDL_GetWindowSurface(env->window);
    
    if (!env->surface) {
        fatal("Could not initialize window.");
    }
    
    return env;
}
