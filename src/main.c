#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "common.h"
#include "env.h"

/*
  Log at given level into stdout.
  TODO: refactor logging logic into its own file.
*/
void error(char *err) {
    printf("%s\n", err);
}

/*
  initGameEngine
  Entry point for the engine. initialize the environment structure with all
  necessary elements and setup SDL.
*/
struct env_t *initGameEngine() {
    struct env_t *env = NULL;
    env = malloc(sizeof(struct env_t));

    if (!env) {
        error("Could not create environment.");
        exit(1);
    }

    env->window  = NULL;
    env->surface = NULL;

    env->window = SDL_CreateWindow(WINDOW_TITLE,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   WIDTH,
                                   HEIGHT,
                                   SDL_WINDOW_SHOWN
                                   );

    if (!env->window) {
        error("ERROR: Could not initialize a SDL window.");
        exit(1);
    }

    env->surface = SDL_GetWindowSurface(env->window);
    if (!env->surface) {
        error("ERROR: Could not initialize SDL surface.");
        exit(1);
    }

    return env;
}

/*
  Deallocate all structures declared during runtime for the engine.
*/
void exitEngine(struct env_t *env) {
    SDL_DestroyWindow(env->window);
    SDL_FreeSurface(env->surface);
    free(env);
}

int main(int argc, char **argv) {
    if (SDL_INIT_EVERYTHING < 0) {
        error("ERROR: Could not start SDL.");
        return 1;
    }

    struct env_t *env = initGameEngine();
    
    return 0;
}
