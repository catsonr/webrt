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
    void setSegment(const Point& p1, const Point& p2)
    {
        r = Ray(p1, p2 - p1, rt::RAY_EPSILON, 1.0f - rt::RAY_EPSILON);
    }

    void setRay(const Point& p, const Vector& w)
    {
        r = Ray(p, w, rt::RAY_EPSILON);
    }
    
    /*
    bool unoccluded(const Scene* scene) const
    {
        return !scene->intersectP(r);
    }
    */
    
    /*
    Spectrum transmittance(const Scene* scene) const
    {
        return scene->transmittance(r);
    }
    */
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
    virtual bool isDeltaLight() const = 0;
};


#endif