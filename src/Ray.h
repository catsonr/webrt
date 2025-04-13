#ifndef RAY_H
#define RAY_H

#include "Point.h"

class Ray
{
    public:
        Ray(Point o, Vector d);
        
        Point operator()(float t) const;
        
        mutable float t_min, t_max;

        Point o;
        Vector d;
};

#endif