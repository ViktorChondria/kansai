#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "graphics.h"
#include "text.h"

int main(int argc, char **argv) {
    setupWindow();
    initText();

    int initTick;
    int running = 1;
    SDL_Event e;

    loadBackground("./assets/img/bg0.png");
    loadHud("./assets/img/hud.png");
    loadLeftChar("./assets/img/mia.png");
    drawText("TEST");

    /* main engine loop */
    while (running) {
        initTick = SDL_GetTicks(); // set the start time for the loop iteration

        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                running = 0;
            }
        }

        // limit framerate to MAX_FRAMES.
        int deltaTime = (SDL_GetTicks() - initTick); 
        if((1000 / MAX_FRAMES) > deltaTime){
            SDL_Delay((1000 / MAX_FRAMES) - deltaTime); // limit FPS to MAX_FRAMES
        }
    }

    cleanupText();
    clearSDL();
    return 0;
}
