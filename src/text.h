#ifndef _KANSAI_TEXT_
#define _KANSAI_TEXT_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void initText();
void cleanupText();
SDL_Surface *renderText(char *text, SDL_Color color);

#endif
