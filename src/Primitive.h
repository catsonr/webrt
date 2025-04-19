/*
    Primitive is the abstract base class for all Primitive types (see GeometricPrimitive and InstancePrimitive.)
    primitives are the data structure that contains information about the material of the object
    it is assigned to. primitives do no concern themselves with geometry. for that, there is Shape
*/

#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <vector>
#include <memory>

//#include "Intersection.h" // not included to break circular definition
#include "Ray.h"
#include "Bbox.h"
#include "DifferentialGeometry.h"
#include "BSDF.h"
#include "AreaLight.h"

struct Intersection;

class Primitive : public std::enable_shared_from_this<Primitive>
{
public:
    /* VIRTUAL PUBLIC FUNCTIONS */
    virtual Bbox worldBound() const = 0;

    virtual bool canIntersect() const;
    virtual bool intersects(const Ray& r, Intersection* intersection) const = 0;
    virtual bool intersectsP(const Ray& r) const = 0;
    virtual void refine(std::vector<std::shared_ptr<Primitive>>& refined) const;
    
    virtual BSDF* getBSDF(const DifferentialGeometry& dg, const Transform& world_to_object) const = 0;
    
    virtual const AreaLight* getAreaLight() const = 0;

    //virtual const AreaLight* getAreaLight() const = 0;
    //virtual BSDF* getBSDF(const DifferentialGeometry& dg, const Transform& world_to_object) const = 0;
    
    /* PUBLIC FUNCTIONS */
    void fullyRefine(std::vector<std::shared_ptr<Primitive>>& refined) const;
};

#endif