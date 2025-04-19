#include "Sample.h"

Sample::Sample(SurfaceIntegrator* surf, VolumeIntegrator* vol, const Scene* scene)
{
    
}

Sampler::Sampler(int x_start, int x_end, int y_start, int y_end, int samplesPerPixel) :
    x_start(x_start),
    x_end(x_end),
    y_start(y_start),
    y_end(y_end),
    samplesPerPixel(samplesPerPixel)
{}

int Sampler::totalSamples() const
{
    return samplesPerPixel * (x_end - x_start) * (y_end - y_start);
}