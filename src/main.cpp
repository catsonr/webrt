#include <emscripten.h>
#include <SDL/SDL.h>

#include <stdio.h>

#include "globals.h"
#include "Point.h"
#include "Transform.h"

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
            const float b = 0.5f;
            const float a = 1.0f;

            *((Uint32*)screen->pixels + j * CANVAS_WIDTH + i) = SDL_MapRGBA(screen->format, r*255, g*255, b*255, a*255);
        }
    }

    if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);

    SDL_Flip(screen);

    SDL_Quit();
    
    Point p1(0.0, 0.1, 0.2);
    Point p2(0.1, 0.2, 0.3);
    
    Vector v = p1 - p2;
    
    printf("%f %f %f\n", v.x, v.y, v.z);
    
    Normal n(v);
    
    printf("%f %f %f\n", n.x, n.y, n.z);
    
    Transform t;
    
    t(v);

    printf("%f %f %f\n", v.x, v.y, v.z);

    return 0;
}