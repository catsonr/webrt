#include "Scene.h"

Scene::Scene(Primitive* aggregate, std::vector<Light*> lights, Camera* camera, SurfaceIntegrator* surfaceIntegrator, VolumeIntegrator* volumeIntegrator, Sampler* sampler) :
    aggregate(aggregate),
    lights(lights),
    camera(camera),
    surfaceIntegrator(surfaceIntegrator),
    volumeIntegrator(volumeIntegrator),
    sampler(sampler),
    bound(aggregate->worldBound())
{}

void Scene::render()
{
    Sample* sample = new Sample(surfaceIntegrator, volumeIntegrator, this);
}

bool Scene::intersects(const Ray& ray, Intersection* intersection) const
{
    return aggregate->intersects(ray, intersection);
}

bool Scene::intersectsP(const Ray& ray) const
{
    return aggregate->intersectsP(ray);
}

const Bbox Scene::worldBound() const
{
    return bound;
}

Spectrum Scene::Li(const RayDifferential& ray, const Sample* sample, float* alpha) const
{
    Spectrum Lo = surfaceIntegrator->Li(this, ray, sample, alpha);
    Spectrum T = volumeIntegrator->transmittance(this, ray, sample, alpha);
    Spectrum Lv = volumeIntegrator->Li(this, ray, sample, alpha);

    return T * Lo + Lv;
}

Spectrum Scene::transmittance(const Ray& ray) const
{
    return volumeIntegrator->transmittance(this, ray, NULL, NULL);
}