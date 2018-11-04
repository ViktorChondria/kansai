#ifndef ENV_H

/*
  env_t
  main environment for the game to maintain SDL state.
  Typically this might be implemented in some sort of
  Engine class.
*/
struct env_t {
    SDL_Window *window;
    SDL_Surface *surface;
};

#endif
#define ENV_H
