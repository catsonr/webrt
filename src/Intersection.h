/*
    Intersection holds information about a ray-object intersection
*/

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Primitive.h"
#include "DifferentialGeometry.h"
#include "Transform.h"
#include "BSDF.h"
#include "AreaLight.h"

class Primitive;

struct Intersection
{
    /* CONSTRUCTORS */
    Intersection();

    /* PUBLIC MEMBERS */
    DifferentialGeometry dg;
    const Primitive* primitive;
    Transform world_to_object;

    /* PUBLIC FUNCTIONS */
    BSDF* getBSDF(const RayDifferential& ray) const
    {
        dg.computeDifferentials(ray);
        
        return primitive->getBSDF(dg, world_to_object);
    }
    
    Spectrum Le(const Vector& w) const
    {
        const AreaLight* area = primitive->getAreaLight();
        
        return area ? area->L(dg.p, dg.nn, w) : Spectrum(0.0f);
    }
};

#endif
