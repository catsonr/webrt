/*
    Intersection holds information about a ray-object intersection
*/

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Primitive.h"
#include "DifferentialGeometry.h"
#include "Transform.h"

class Primitive;

struct Intersection
{
    // struct public data
    DifferentialGeometry dg;
    const Primitive* primitive;
    Transform world_to_object;

};

#endif
