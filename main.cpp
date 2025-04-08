#include <stdio.h>
#include <SDL/SDL.h>

#include <emscripten.h>

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);

    if (SDL_MUSTLOCK(screen))
        SDL_LockSurface(screen);
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            const float r = (float)i / WIDTH;
            const float g = (float)j / HEIGHT;
            const float b = 1.0f;
            const float a = 1.0f;

            *((Uint32 *)screen->pixels + j * WIDTH + i) = SDL_MapRGBA(screen->format, r*255, g*255, b*255, a*255);
        }
    }
    if (SDL_MUSTLOCK(screen))
        SDL_UnlockSurface(screen);
    SDL_Flip(screen);

    SDL_Quit();

    return 0;
}