#ifndef SAMPLER_H
#define SAMPLER_H

struct Sample
{
    float imageX, imageY;
    float lensU, lensV;
    float time;
};

class Sampler
{
public:
    Sampler(int xstart, int xend, int ystart, int yend, int samplesPerPixel);
    
    virtual bool getNextSample(Sample* sample) = 0;
    
    int totalSamples() const;
    
    int xPixelStart, xPixelEnd, yPixelStart, yPixelEnd;
    int samplesPerPixel;
};

#endif