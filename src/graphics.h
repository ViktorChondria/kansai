#ifndef _KANSAI_GRAPHICS_
#define _KANSAI_GRAPHICS_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define MAX_FRAMES 30

#define WIDTH 800
#define HEIGHT 600

/* core surface definition constants */
#define S_BACKGROUND_X 0
#define S_BACKGROUND_Y 0 /* w/h are WIDTH / HEIGHT */

#define S_INFO_X (WIDTH / 2)
#define S_INFO_Y (HEIGHT / 2)
#define S_INFO_W (WIDTH / 2)
#define S_INFO_H (HEIGHT / 2)

#define S_TEXT_X 50
#define S_TEXT_Y 480 /* TODO */
#define S_TEXT_W WIDTH
#define S_TEXT_H S_TEXT_Y

#define S_NAME_X 50
#define S_NAME_Y 440
#define S_NAME_W WIDTH
#define S_NAME_H S_TEXT_Y

#define S_CHAR_LEFT_X 200 /* TODO */
#define S_CHAR_LEFT_Y 0

#define S_CHAR_CENTER_X 0
#define S_CHAR_CENTER_Y 0

#define S_CHAR_RIGHT_X 0
#define S_CHAR_RIGHT_Y 0

#define S_CHAR_W 600 /* TODO */
#define S_CHAR_H 600

#define S_HUD_X 0
#define S_HUD_Y 0


void setupWindow();
void clearSDL();
void clearWindow();
void updateWindow();
void drawWindow();

void drawCoreSurface(SDL_Surface *surface, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
void loadCoreSurface(SDL_Surface **sprite, char *filename);

void loadBackground(char *filename);
void loadHud(char *filename);
void loadRightChar(char *filename);
void loadCenterChar(char *filename);
void loadLeftChar(char *filename);

void setName(char *text);
void drawText(char *text);


#endif
