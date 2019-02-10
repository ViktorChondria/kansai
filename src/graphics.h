#ifndef _KANSAI_GRAPHICS_
#define _KANSAI_GRAPHICS_

#include <SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct graphics_node_t {
    struct graphics_node_t *next;
    SDL_Surface *sprite;
    uint8_t marked;
} graphics_node_t;

void setupWindow();
inline void clearWindow();
void appendGraphicsNode(SDL_Surface *surface);


#endif
