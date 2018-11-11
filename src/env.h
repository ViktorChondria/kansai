#include <SDL2/SDL.h>
#ifndef _KANSAI_ENV_
#define _KANSAI_ENV_

struct env_t {
    SDL_Surface *surface;
    SDL_Window *window;
};

struct env_t *createEnvironment();

#endif
