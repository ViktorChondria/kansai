#ifndef _KANSAI_WINDOW_
#define _KANSAI_WINDOW_

#define WIDTH 800
#define HEIGHT 600

#include "env.h"
#include "entity.h"
void clearWindow(env_t *env);
/* TODO: cache loaded files. */
void drawSprite(env_t *env, entity_t *entity);

#endif
