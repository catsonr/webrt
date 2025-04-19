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
    
    virtual Point sample(float u1, float u2, Normal *Ns) const {
        printf("unimplemented Shape::sample() method called!");
        return Point();
    }
    
    // members
    Transform object_to_world, world_to_object;
    bool reverseOrientation, transformSwapsHandedness;
};

class ShapeSet : public Shape
{
public:
    /* PUBLIC METHODS */
    Point sample(float u1, float u2, Normal* Ns) const
    {
        float ls = (float)rand() / (float)rand(); // in future, use pbrt RandomFloat()
        int sn;

        for(sn = 0; sn < shapes.size() -1; sn++)
            if(ls < areaCDF[sn]) 
                break;
        
        return shapes[sn]->sample(u1, u2, Ns);
    }

private:
    std::vector<std::shared_ptr<Shape>> shapes;
    float area;
    std::vector<float> areaCDF;
};

#endif