#include <emscripten.h>
#include <SDL/SDL.h>

#include <stdio.h>

#include "globals.h"

#include "Point.h"
#include "Vector.h"
#include "Normal.h"
#include "Transform.h"

//#include "bruh.h"

bool mathExam()
{
    Vector v1(1, 2, 3);
    Vector v2(10, 10, 10);
    
    v1 = v1 + v2;
    v1 += v2;
    
    printf("%f %f %f\n", v1.x, v1.y, v1.z);
    
    Normal n(v1);
    Normal normalized = normalize(n);
    
    printf("%f %f %f\n", normalized.x, normalized.y, normalized.z);
    
    Vector vnorm = normalize(v2);
    
    printf("%f %f %f\n", vnorm.x, vnorm.y, vnorm.z);
    
    Transform T;
    
    T.m->print();
    T = T.translate(Vector(1, 2, 3));
    
    T.m->print();
    
    T.mInv->print();
    
    Transform lookat;
    lookat = lookat.lookAt(Point(1.5, 3, 5), Point(-12, 4, 2), Vector(0, 1, 0));
    
    printf("lookat:\n");
    lookat.m->print();
    
    return true;
}

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
    
    mathExam();

    return 0;
}