#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Primitive.h"
#include "Light.h"
#include "Camera.h"
#include "Sample.h"
#include "Integrator.h"

class Scene
{
public:
    /* PUBLIC MEMBERS */
    Primitive* aggregate;
    std::vector<Light*> lights;
    Camera* camera;
    //SurfaceIntegrator* surfaceIntegrator;
    //VolumeIntegrator* volumeIntegrator;
    Sampler* sampler;

    //VolumeRegion* volumeRegion; // described in chapter 12

private:
};

#endif
