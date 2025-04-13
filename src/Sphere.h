#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"
#include "globals.h"

class Sphere : public Shape
{
public:
    Sphere(
        const Transform& object_to_world,
        bool reverseOrientation,
        float radius,
        float z0, float z1,
        float maxPhi
    );
    
    virtual Bbox objectBound() const override;
    virtual bool intersects(const Ray& ray, float* t_hit, DifferentialGeometry* dg) const override;

private:
    float radius;
    float phi_max;
    float z_min, z_max;
    float theta_min, theta_max;
};

#endif