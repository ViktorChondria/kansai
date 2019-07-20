#include "log.h"
#include "graphics.h"

#define CHECK_WINDOW if (gsurface == NULL || gsurface == NULL) { fatal("Window must be setup"); }

/* global references to the Kansai window context */
SDL_Surface *gsurface = NULL;
SDL_Window *gwindow = NULL;

/* 
   in Kansai, the window is split into 6 "core surfaces" in draw order top->bottom:
     - an information / image display screen (think like Steins;Gate's image displays)
     - the text window
     - 3 on-screen characters and
     - the background

     **************************************
     *                                    *
     *                                    *
     *            ************            *
     *            *   INFO   *            *
     *            * (behind) *            *
     *   CLCLCL   *  CCCCCC  *   CRCRCR   *
     *   CLCLCL   *  CCCCCC  *   CRCRCR   *
     *            ************   CRCRCR   *
     **************************************
     *   TEXT TEXT TEXT TEXT TEXT TEXT    *
     *   TEXT TEXT TEXT TEXT TEXT TEXT    *
     *   TEXT TEXT TEXT TEXT TEXT TEXT    *
     *                                    *
     **************************************

   
   in the event that some section requires a custom section, it must be handled
   inside of that scene and operate independently. This means all clean-up etc.
   is NOT assumed unless it is using one of these 6 core surfaces.
*/
SDL_Surface *s_background;
SDL_Surface *s_info;
SDL_Surface *s_text;
SDL_Surface *s_charLeft;
SDL_Surface *s_charCenter;
SDL_Surface *s_charRight;

/* needs to be called prior to any other graphics calls */
void setupWindow() {
    /* setup SDL */
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fatal("Could not start SDL.");
    }
    
    /* initialize the shared resources */
    gwindow = SDL_CreateWindow("Kansai",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   WIDTH,
                                   HEIGHT,
                                   SDL_WINDOW_SHOWN);
    if (!gwindow) {
        fatal("Could not initialize window.");
    }

    gsurface = SDL_GetWindowSurface(gwindow);
    
    if (!gsurface) {
        fatal("Could not initialize window.");
    }
    s_background = NULL;
    s_info = NULL;
    s_text = NULL;
    s_charLeft = NULL;
    s_charCenter = NULL;
    s_charRight = NULL;
}

void clearWindow() {
    CHECK_WINDOW;
    SDL_FillRect(gsurface,
                 NULL,
                 SDL_MapRGB(gsurface->format, 255, 255, 255));
}

void updateWindow() {
    CHECK_WINDOW;
    SDL_UpdateWindowSurface(gwindow);
}

/* perform SDL cleanup */
void clearSDL() {
    /* TODO: more advanced cleanup */
    SDL_DestroyWindow(gwindow);
    SDL_Quit();
}

void drawImage(char *filename, uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    CHECK_WINDOW;

    SDL_Surface *sprite = NULL;
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.w = w;
    srcRect.h = h;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.w = w;
    destRect.h = h;
    destRect.x = x;
    destRect.y = y;

    sprite = SDL_LoadBMP(filename);

    if (!sprite) {
        fatal("Could not load image", filename);
    }

    /* key out white for background transparecy. */
    SDL_SetColorKey(sprite, SDL_TRUE,
                    SDL_MapRGB(sprite->format, 255, 255, 255));

    if (!sprite) {
        fatal("Could not key out file %s", filename);
    }
    
    SDL_BlitSurface(sprite, &srcRect, gsurface, &destRect);
}

void drawCoreSurface(SDL_Surface *surface, uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    if (surface == NULL) return;

    CHECK_WINDOW;

    /* this entire code section is stupid easy to optimize just by passing around some context
       but as implementation numero uno I've left this un-done. */
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.w = w;
    srcRect.h = h;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.w = w;
    destRect.h = h;
    destRect.x = x;
    destRect.y = y;

    SDL_BlitSurface(surface, &srcRect, gsurface, &destRect);
}

/* draw the core surfaces */
void drawWindow() {
    /* clear the window */
    clearWindow();

    drawCoreSurface(s_background, S_BACKGROUND_X, S_BACKGROUND_Y, WIDTH, HEIGHT);

    drawCoreSurface(s_charLeft, S_CHAR_LEFT_X, S_CHAR_RIGHT_Y, S_CHAR_W, S_CHAR_H);
    drawCoreSurface(s_charCenter, S_CHAR_CENTER_X, S_CHAR_CENTER_Y, S_CHAR_W, S_CHAR_H);
    drawCoreSurface(s_charRight, S_CHAR_RIGHT_X, S_CHAR_RIGHT_Y, S_CHAR_W, S_CHAR_H);

    drawCoreSurface(s_text, S_TEXT_X, S_TEXT_Y, S_TEXT_W, S_TEXT_H);

    drawCoreSurface(s_info, S_INFO_X, S_INFO_Y, S_INFO_W, S_INFO_H);

    /* redraw the window */
    updateWindow();
}

void loadCoreSurface(SDL_Surface **sprite, char *filename) {
    *sprite = SDL_LoadBMP(filename);

    if (*sprite == NULL) {
        fatal("Could not load image", filename);
    }

    /* key out white for background transparecy. */
    SDL_SetColorKey(*sprite, SDL_TRUE,
                    SDL_MapRGB((*sprite)->format, 255, 255, 255));

    if (*sprite == NULL) {
        fatal("Could not key out file %s", filename);
    }
}