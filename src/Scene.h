#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Primitive.h"
#include "Light.h"
#include "Camera.h"
#include "Sample.h"
#include "Integrator.h"
#include "Bbox.h"
#include "Spectrum.h"

// forward declarations to stop circular definitions
class Camera;
class Sampler;
class SurfaceIntegrator;
class VolumeIntegrator;
class Sample;
class Primitive;
class Light;
class Intersection;

class Scene
{
public:
    /* CONSTRUCTORS */
    Scene(Primitive* aggregate, std::vector<Light*> lights, Camera* camera, SurfaceIntegrator* surfaceIntegrator, VolumeIntegrator* volumeIntegrator, Sampler* sampler);

    /* PUBLIC MEMBERS */
    Primitive* aggregate;
    std::vector<Light*> lights;
    Camera* camera;
    SurfaceIntegrator* surfaceIntegrator;
    VolumeIntegrator* volumeIntegrator;
    Sampler* sampler;
    Bbox bound;

    //VolumeRegion* volumeRegion; // described in chapter 12

    /* PUBLIC METHODS */
    void render();

    bool intersects(const Ray& ray, Intersection* intersection) const;
    bool intersectsP(const Ray& ray) const;

    const Bbox worldBound() const;
    
    Spectrum Li(const RayDifferential& ray, const Sample* sample, float* alpha) const;
    Spectrum transmittance(const Ray& ray) const;

private:
};

#endif
