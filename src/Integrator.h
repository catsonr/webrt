/*
    Integrator is the interface all Integrators impliment
    
*/

#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "Spectrum.h"
#include "Scene.h"
#include "Ray.h"
#include "Sample.h"

class Integrator
{
public:
    virtual Spectrum Li(const Scene* scene, const RayDifferential& ray, const Sample* sample, float* alpha) const = 0;

private:
};

class SurfaceIntegrator : public Integrator
{

};

class VolumeIntegrator : public Integrator
{

};

#endif