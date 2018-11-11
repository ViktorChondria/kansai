#ifndef _KANSAI_WINDOW_
#define _KANSAI_WINDOW_

#define WIDTH 800
#define HEIGHT 600

#include "env.h"
#include "entity.h"
void clearWindow(struct env_t *env);
/* TODO: cache loaded files. */
void drawSprite(struct env_t *env, struct entity_t *entity);

#endif
