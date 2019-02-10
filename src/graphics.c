#include "log.h"
#include "graphics.h"

#define CHECK_WINDOW if (gsurface == NULL || gsurface == NULL) { fatal("Window must be setup"); }

/* global references to the Kansai window context */
SDL_Surface *gsurface = NULL;
SDL_Window *gwindow = NULL;

/* linked list maintaining all currently active sprites */
graphics_node_t *head;

/* needs to be called prior to any other graphics calls */
void setupWindow() {
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

    head = malloc(sizeof(graphics_node_t));
    head->next = NULL;
    head->sprite = NULL;
    head->marked = 0; /* head is never marked */
}

inline void clearWindow() {
    CHECK_WINDOW;
    SDL_FillRect(gsurface,
                 NULL,
                 SDL_MapRGB(gsurface->format, 255, 255, 255));
}

inline void updateWindow() {
    CHECK_WINDOW;
    SDL_UpdateWindowSurface(gwindow);
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

    appendGraphicsNode(sprite);
    
    SDL_BlitSurface(sprite, &srcRect, gsurface, &destRect);
}


void appendGraphicsNode(SDL_Surface *surface) {
    graphics_node_t *curNode = head;
    /* traverse the list to find the next free node */
    while (curNode->next != NULL) {
        /* whenever a new node is appended, cleanup the old ones */
        if (curNode->next->marked) {
            SDL_FreeSurface(curNode->next->sprite); /* clean up SDL's memory */
            curNode->next = (curNode->next->next == NULL)
                ? NULL
                : curNode->next->next;
            free(curNode->next); /* clean up our allocated memory */
        }
        curNode = curNode->next;
    }

    /* allocate the new current node */
    curNode->next = malloc(sizeof(graphics_node_t));
    curNode->next->sprite = surface;
    curNode->next->marked = 0;
    curNode->next->next = NULL;
}
