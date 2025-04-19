#include "Ray.h"

Ray::Ray() :
    o(Point()),
    d(Vector()),
    t_min(rt::RAY_EPSILON),
    t_max(INFINITY),
    t(0.0f)
{}
Ray::Ray(const Point& origin, const Vector& direction, float start, float end, float t) :
    o(origin),
    d(direction),
    t_min(start),
    t_max(end),
    t(t)
{}

Point Ray::operator()(float t) const
{
    return o + d*t;
}