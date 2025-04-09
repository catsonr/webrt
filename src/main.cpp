#include <emscripten.h>
#include <wasm_simd128.h>

#include <SDL/SDL.h>

#include <stdio.h>
#include "globals.h"
#include "Camera.h"

void simdTest() 
{
    printf("simd test\n");

    float v1[4] = { 0.2f, 0.2f, 0.3f, 1.0f };
    float v2[4] = { 0.2f, 0.1f, 0.0f, 0.0f };
    float out[4] = { 0 };
    
    v128_t v1_simd = wasm_v128_load(v1);
    v128_t v2_simd = wasm_v128_load(v2);
    
    v128_t sum_simd = wasm_f32x4_add(v1_simd, v2_simd);
    
    wasm_v128_store(&out, sum_simd);
    
    printf("after addition: %f %f %f %f\n", out[0], out[1], out[2], out[3]);
    
    //fflush(stdout);
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
            const float b = 1.0f;
            const float a = 1.0f;

            *((Uint32*)screen->pixels + j * CANVAS_WIDTH + i) = SDL_MapRGBA(screen->format, r*255, g*255, b*255, a*255);
        }
    }

    if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);

    SDL_Flip(screen);

    SDL_Quit();
    
    Camera* c = new Camera();

    return 0;
}