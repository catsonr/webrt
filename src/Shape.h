#ifndef SHAPE_H
#define SHAPE_H

#include <memory>

#include "Transform.h"
#include "Bbox.h"
#include "DifferentialGeometry.h"

class DifferentialGeometry;

class Shape
{
public:
    // constructors 
    Shape(const Transform& T_objectToWorld, bool reverseOrientation);
    
    // virtual functions 
    virtual Bbox objectBound() const = 0;
    virtual Bbox worldBound() const { return object_to_world(objectBound()); }

    virtual bool canIntersect() const
    {
        return true;
    }
    virtual void refine(std::shared_ptr<Shape>& refined) const
    {
        printf("unimplimented Shape::refine() method called!");
    }

    virtual bool intersects(const Ray& ray, float* tHit, DifferentialGeometry* dg) const
    {
        printf("unimplimented Shape::intersects() method called!");
        
        return false;
    }
    virtual bool intersectsP(const Ray& ray) const
    {
        printf("unimplimented Shape::intersectsP() method called!");
        
        return false;
    }
    
    /*virtual void getShadingGeometry(const Transform& otw,
        const DifferentialGeometry& dg,
        const DifferentialGeometry* dgShading) const
    {
        *dgShading = dg;
    }*/
    
    virtual float area() const
    {
        printf("unimplimented Shape::area() method called!");
        
        return NAN;
    }
    
    // members
    Transform object_to_world, world_to_object;
    bool reverseOrientation, transformSwapsHandedness;
};

#endif