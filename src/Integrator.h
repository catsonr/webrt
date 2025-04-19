/*
    Integrator is the interface all Integrators impliment
*/

#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "Spectrum.h"
#include "Scene.h"
#include "Ray.h"
#include "Sample.h"

class Sample;
class Scene;

class Integrator
{
public:
    virtual Spectrum Li(const Scene* scene, const RayDifferential& ray, const Sample* sample, float* alpha) const = 0;
    virtual void preprocess(const Scene* scene);
    virtual void requestSamples(Sample* sample, const Scene* scene);

private:
};

class SurfaceIntegrator : public Integrator
{
public:
};

class VolumeIntegrator : public Integrator
{
public:
    virtual Spectrum transmittance(const Scene* scene, const Ray& ray, const Sample* sample, float* alpha) const = 0;
};

#endif