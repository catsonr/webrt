#include <emscripten.h>
#include <SDL/SDL.h>

#include <stdio.h>

#include "globals.h"
#include "RTIOW.h"

#include "Camera.h"

SDL_Surface* init()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* screen = SDL_SetVideoMode(rt::CANVAS_WIDTH, rt::CANVAS_HEIGHT, 32, SDL_SWSURFACE); // 32 bpp, 8 bits each for R, G, B, A

    return screen;
}

int main(int argc, char **argv)
{
    // create SDL screen to draw on
    SDL_Surface* screen = init();
    printf("SDL initialized!\n");

    // generate and draw frame of RTIOW
    OW::run(screen);
    
    // closing
    SDL_Quit();
    fflush(stdout);
    return 0;
}