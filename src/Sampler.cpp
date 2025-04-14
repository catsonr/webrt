#include "Sampler.h"

Sampler::Sampler(int xstart, int xend, int ystart, int yend, int samplesPerPixel) :
    xPixelStart(xstart),
    xPixelEnd(xend),
    yPixelStart(ystart),
    yPixelEnd(yend),
    samplesPerPixel(samplesPerPixel)
{}

int Sampler::totalSamples() const
{
    return samplesPerPixel * (xPixelEnd - xPixelStart) * (yPixelEnd - yPixelStart);
}