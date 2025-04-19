/*
    a Sampler generates a Sample at a given x, y coordinate
    Samplers require a SurfaceIntegrator and VolumeIntegrator to sample from
*/
#ifndef SAMPLE_H
#define SAMPLE_H

#include "Integrator.h"

class SurfaceIntegrator;
class VolumeIntegrator;

struct Sample
{
    /* PUBLIC MEMBERS */
    float imageX, imageY;
    float lensU, lensV;
    float time;
    
    /* CONSTRUCTORS */
    Sample(SurfaceIntegrator* surf, VolumeIntegrator* vol, const Scene* scene);
};

class Sampler
{
public:
    /* CONSTRUCTORS */
    Sampler(int x_start, int x_end, int y_start, int y_end, int samplesPerPixel);
    
    /* ABSTRACT PUBLIC FUNCTIONS */
    virtual bool getNextSample(Sample* sample) = 0;
    
    /* PUBLIC FUNCTIONS */
    // returns the number of samples
    int totalSamples() const;
    
    /* PUBLIC MEMBERS */
    int x_start, x_end, y_start, y_end;
    int samplesPerPixel;
};

#endif