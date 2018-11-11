#include <SDL2/SDL.h>
#include "window.h"

inline void clearWindow(struct env_t *env) {
    SDL_FillRect(env->surface,
                 NULL,
                 SDL_MapRGB(env->surface->format, 255, 255, 255));
}

void drawSprite(struct env_t *env, struct entity_t *entity) {
    /* if the sprite isn't onscreen, do nothing.*/
    if (entity->x > WIDTH  ||
        entity->x < 0      ||
        entity->y > HEIGHT ||
        entity->y < 0      ) {
        return;
    }
    SDL_BlitSurface(entity->sprite,
                    &entity->rect,
                    env->surface,
                    &entity->destRect);
}
