#include "Ray.h"

#define RAY_EPSILON 1e-3f

Ray::Ray(Point o, Vector d) :
    o(o),
    d(d),
    t_min(RAY_EPSILON),
    t_max(INFINITY)
{}

Point Ray::operator()(float t) const
{
    return o + d*t;
}