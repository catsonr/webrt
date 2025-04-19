#include "Light.h"

void VisibilityTester::setSegment(const Point &p1, const Point &p2)
{
    r = Ray(p1, p2 - p1, rt::RAY_EPSILON, 1.0f - rt::RAY_EPSILON);
}

void VisibilityTester::setRay(const Point &p, const Vector &w)
{
    r = Ray(p, w, rt::RAY_EPSILON);
}

bool VisibilityTester::unoccluded(const Scene *scene) const
{
    return !scene->intersectsP(r);
}

Spectrum VisibilityTester::transmittance(const Scene *scene) const
{
    return scene->transmittance(r);
}