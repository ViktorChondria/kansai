#include <stdint.h>
#include <math.h>

#include "log.h"
#include "text.h"

/* global SDL context */
TTF_Font *gfont;
TTF_Font *gfontBold;

/* TODO: format strings & custom bold
   ie: "%bINFO%\b %s: %s", playerName, message
*/
SDL_Surface *renderText(char *text, SDL_Color color) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(gfont, text, color);
    if (textSurface == NULL) {
        fatal("Could not load text %s.", text);
    }

    return textSurface;
}

/* must be called before text is used. */
void initText() {
    if (TTF_Init() == -1) {
        fatal("SDL_ttf could not be initialized: %s", TTF_GetError());
    }

    /* load the ttf fonts and store them in global context */
    gfont = TTF_OpenFont("./assets/font/roboto_light.ttf", 28);
    gfontBold = TTF_OpenFont("./assets/font/roboto_bold.ttf", 28);
}

/* TODO: more intricate cleanup */
void cleanupText() {
    TTF_CloseFont(gfont);
    TTF_CloseFont(gfontBold);
    TTF_Quit();
}
