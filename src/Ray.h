#ifndef RAY_H
#define RAY_H

#include "Point.h"

class Ray
{
    public:
        Ray();
        Ray(Point origin, Vector direction);
        
        Point operator()(float t) const;
        
        mutable float t_min, t_max;

        Point o;
        Vector d;
};

class RayDifferential : public Ray
{
public:
    bool hasDifferentials;
    Ray rx, ry;

    RayDifferential() :
        hasDifferentials(false)
    {}
    RayDifferential(const Point& origin, const Vector& direction) :
        Ray(origin, direction),
        hasDifferentials(false)
    {}
    explicit RayDifferential(const Ray& ray) :
        Ray(ray),
        hasDifferentials(false)
    {}

private:
};

#endif