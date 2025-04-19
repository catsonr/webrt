#ifndef DIFFERENTIAL_GEOMETRY_H
#define DIFFERENTIAL_GEOMETRY_H

#include "Point.h"
#include "Vector.h"
#include "Normal.h"
#include "Shape.h"

class Shape;

class DifferentialGeometry
{
public:
    /* CONSTRUCTORS */
    DifferentialGeometry() :
        u(0.0f),
        v(0.0f),
        shape(NULL)
    {}
    DifferentialGeometry(const Point& P,
            const Vector& DPDU, const Vector& DPDV,
            const Vector& DNDU, const Vector& DNDV,
            float uu, float vv, const Shape* sh
    );

    /* PUBLIC MEMBERS */
    Point p;
    Normal nn;
    float u, v;
    const Shape* shape;
    Vector dpdu, dpdv;
    Vector dndu, dndv;
    
    mutable Vector dpdx, dpdy;
    mutable float dudx, dvdx, dudy, dvdy;
    
    /* PUBLIC METHODS */
    void computeDifferentials(const RayDifferential& ray) const;
};

#endif