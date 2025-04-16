#include "GeometricPrimitive.h"

// constructors
GeometricPrimitive::GeometricPrimitive(const std::shared_ptr<Shape>& shape) :
    shape(shape)
{}
/*
GeometricPrimitive(const std::shared_ptr<Shape>& shape, const std::shared_ptr<Material>& material, AreaLight* areaLight) :
    shape(shape),
    material(material),
    areaLight(areaLight)
{}
*/

// public function overloads
Bbox GeometricPrimitive::worldBound() const
{
    return shape->worldBound();
}

bool GeometricPrimitive::canIntersect() const
{
    return shape->canIntersect();
}

bool GeometricPrimitive::intersects(const Ray& r, Intersection* intersection) const
{
    float tAtHit;

    if(!shape->intersects(r, &tAtHit, &intersection->dg))
        return false;
    
    intersection->primitive = this;
    intersection->world_to_object = shape->world_to_object;
    r.t_max = tAtHit;

    return true;
}

bool GeometricPrimitive::intersectsP(const Ray& r) const
{
    return shape->intersectsP(r);
}