#include "RTIOW.h"

#include "Ray.h"

// renders a single frame
// saves result in SDL_Surface screen's pixel member
void OW::run(SDL_Surface* screen)
{
    printf("OW::samplePixels() : sampling all pixels ...\n");

    // ask for permission to draw to screen
    if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);
    
    Uint32* pixels = static_cast<Uint32*>(screen->pixels);
    int stride = screen->pitch / sizeof(Uint32);
    int w = screen->w;
    int h = screen->h;
    
    for(int j = 0; j < h; j++)
    {
        for(int i = 0; i < w; i++)
        {
            Color c;
            Uint8 r = 0.0f;
            Uint8 g = 0.0f;
            Uint8 b = 0.0f;
            Uint8 a = 0.0f;
            
            c.quantize(&r, &g, &b, &a);
            
            pixels[j * stride + i] = SDL_MapRGBA(screen->format, r, g, b, a);
        }
    }

    // stop drawing to screen
    if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);

    // update canvas
    SDL_Flip(screen);
}

OW::Color OW::calculatePixelColor(Sample& sample)
{
    return Color();
}