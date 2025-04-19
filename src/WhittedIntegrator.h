#ifndef WHITTEDINTEGRATOR_H
#define WHITTEDINTEGRATOR_H

#include "Intersection.h"
#include "Integrator.h"
#include "BSDF.h"

class WhittedIntegrator : public SurfaceIntegrator
{
public:
    Spectrum Li(const Scene* scene, const RayDifferential& ray, const Sample* sample, float* alpha) const override;
    
private:
    int maxDepth;
    mutable int rayDepth;
};

#endif