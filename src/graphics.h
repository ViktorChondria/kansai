#ifndef _KANSAI_GRAPHICS_
#define _KANSAI_GRAPHICS_

#include <SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 600

/* core surface definition constants */
#define S_BACKGROUND_X 0
#define S_BACKGROUND_Y 0 /* w/h are WIDTH / HEIGHT */

#define S_INFO_X WIDTH / 2
#define S_INFO_Y HEIGHT / 2
#define S_INFO_W WIDTH / 2
#define S_INFO_H HEIGHT / 2

#define S_TEXT_X 0
#define S_TEXT_Y (HEIGHT / 3) * 2
#define S_TEXT_W WIDTH
#define S_TEXT_H S_TEXT_Y

#define S_CHAR_LEFT_X 0 /* TODO */
#define S_CHAR_LEFT_Y 0

#define S_CHAR_CENTER_X 0
#define S_CHAR_CENTER_Y 0

#define S_CHAR_RIGHT_X 0
#define S_CHAR_RIGHT_Y 0

#define S_CHAR_W 50 /* TODO */
#define S_CHAR_H 50


void setupWindow();
void clearSDL();
void clearWindow();
void updateWindow();
void drawWindow();

void drawCoreSurface(SDL_Surface *surface, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
void loadCoreSurface(SDL_Surface **sprite, char *filename);


#endif
