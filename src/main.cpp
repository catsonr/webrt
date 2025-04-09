#include <emscripten.h>
//#include <wasm_simd128.h>

#include <SDL/SDL.h>

#include <stdio.h>
#include "globals.h"

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* screen = SDL_SetVideoMode(CANVAS_WIDTH, CANVAS_HEIGHT, 0, SDL_SWSURFACE);

    if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);

    for (int i = 0; i < CANVAS_WIDTH; i++)
    {
        for (int j = 0; j < CANVAS_HEIGHT; j++)
        {
            const float r = (float)i / CANVAS_WIDTH;
            const float g = (float)j / CANVAS_HEIGHT;
            const float b = 1.0f;
            const float a = 1.0f;

            *((Uint32*)screen->pixels + j * CANVAS_WIDTH + i) = SDL_MapRGBA(screen->format, r*255, g*255, b*255, a*255);
        }
    }

    if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);

    SDL_Flip(screen);

    SDL_Quit();

    return 0;
}