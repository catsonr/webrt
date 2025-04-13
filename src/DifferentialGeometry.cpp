#include "DifferentialGeometry.h"

DifferentialGeometry::DifferentialGeometry(const Point& P,
        const Vector& DPDU, const Vector& DPDV,
        const Vector& DNDU, const Vector& DNDV,
        float uu, float vv, const Shape* sh) :
    p(P),
    dpdu(DPDU),
    dpdv(DPDV),
    dndu(DNDU),
    dndv(DNDV),
    nn(normalize(cross(dpdu, dpdv))),
    u(uu),
    v(vv),
    shape(sh)
{
    if(shape->reverseOrientation ^ shape->transformSwapsHandedness)
        nn *= -1.0f;
}