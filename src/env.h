#include <SDL2/SDL.h>
#ifndef _KANSAI_ENV_
#define _KANSAI_ENV_

typedef struct {
    SDL_Surface *surface;
    SDL_Window *window;
} env_t ;

env_t *createEnvironment();

#endif
