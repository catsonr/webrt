#ifndef RAY_H
#define RAY_H

#include "Point.h"

#include "globals.h"

class Ray
{
    public:
        /* PUBLIC MEMBERS */
        Point o;
        Vector d;
        mutable float t_min, t_max;
        float t;

        /* CONSTRUCTORS */
        Ray();
        Ray(const Point& origin, const Vector& direction, float start = rt::RAY_EPSILON, float end = INFINITY, float t = 0.0f);
        
        /* OPERATOR OVERLOADS */
        Point operator()(float t) const;
        
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