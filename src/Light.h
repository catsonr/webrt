/*
    Light is the interface that light subclasses impliment
    VisibilityTester is a closure that contains direct lighting ray cast information
*/

#ifndef LIGHT_H
#define LIGHT_H

#include "Transform.h"
#include "Spectrum.h"
#include "Scene.h"

#include "globals.h"

class Scene;

struct VisibilityTester
{
    /* PUBLIC MEMBERS */
    Ray r;
    
    /* PUBLIC FUNCTIONS */
    void setSegment(const Point& p1, const Point& p2);
    void setRay(const Point& p, const Vector& w);
    
    bool unoccluded(const Scene* scene) const;
    
    Spectrum transmittance(const Scene* scene) const;
};

class Light
{
public:
    /* PUBLIC MEMBERS */
    const Transform light_to_world, world_to_light;
    const int nSamples;

    /* CONSTRUCTORS */
    Light(const Transform& light_to_world, int nSamples = 1) :
        nSamples(nSamples),
        light_to_world(light_to_world)
    {}
    
    /* VIRTUAL PUBLIC FUNCTIONS */
    virtual Spectrum sample_L(const Point& p, Vector* wi, VisibilityTester* vis) const = 0;
    virtual Spectrum power(const Scene* scene) const = 0;
    virtual Spectrum Le(const RayDifferential&) const
    {
        return Spectrum(0.0f);
    }
    virtual bool isDeltaLight() const = 0;
};


#endif