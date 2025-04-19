#ifndef FILM_H
#define FILM_H

#include "Sample.h"
#include "Ray.h"
#include "Spectrum.h"

class Film
{
public:
    const int xResolution, yResolution;

    Film(int xResolution, int yResolution);
    
    virtual void addSample(const Sample& sample, const Ray& ray, const Spectrum& L, float alpha) = 0;
    virtual void writeImage() = 0;
    virtual void getSampleExtent(int* xstart, int* xend, int* ystart, int* yend) = 0;
};

class ImageFilm : public Film
{
public:


private:
};

#endif // FILM_H