/*
    RTIOW.h is an implimentation of Ray Tracing in One Weekend, but using the classes
    defined by pbrt.
    it's a simplied ray tracer implimentation that is used to test if pbrt is functioning correctly
        e.g.: pbrt classes like Point, Vector, Transform all behave as expected
*/

#ifndef RTIOW_H
#define RTIOW_H

#include <SDL/SDL.h>

#include "globals.h"
#include "Sample.h"

struct Color;

// "One Weekend"
namespace OW
{
    struct Color
    {
        /* PUBLIC MEMBERS */
        // defaults to hot pink (if you see hot pink, something's probably wrong!)
        float r = 1.0f;
        float g = 0.3f;
        float b = 0.7f;
        float a = 1.0f;
        
        /* PUBLIC METHODS */
        constexpr void quantize(Uint8* R, Uint8* G, Uint8* B, Uint8* A) const
        {
            *R = static_cast<Uint8>(r * 255 + 0.5f);
            *G = static_cast<Uint8>(g * 255 + 0.5f);
            *B = static_cast<Uint8>(b * 255 + 0.5f);
            *A = static_cast<Uint8>(a * 255 + 0.5f);
        }
    }; // Color

    constexpr static int rgba = 4;

    // runs ray tracing in one weekend :)
    void run(SDL_Surface* screen);
    Color calculatePixelColor(Sample& sample);
}; // ow

#endif