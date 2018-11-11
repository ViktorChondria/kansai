#ifndef _KANSAI_ENTITY_
#define _KANSAI_ENTITY_

#include <stdint.h>
#include "env.h"

/*
  In Kansai, entities are a somewhat abstract concept. For the sake of
  logical simplicity, they're basically just implemented as `objects'
  of a sort. They exist because I needed a system by which I could mai-
  ntain a list of entities in states. The update system is implemented
  for each instance.

  The way I invision the usage is that for each entity-type there will
  be functions like `spawnBasicEnemy()' that will populate this struct
  and will return a pointer that can be called into by the state.
*/
struct entity_t {
    /* screen position. */
    uint32_t x;
    uint32_t y;
    /* sprite size */
    uint32_t w;
    uint32_t h;
    /* sprite */
    SDL_Surface *sprite;
    /* SDL's internal memory map for sprites. */
    SDL_Rect rect;
    SDL_Rect destRect;
    /* update function for entities are kinda simulating OOP
       just for logical simplicity */
    uint32_t (*update)(struct env_t *env, struct entity_t *this);
};

#endif
