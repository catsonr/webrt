/*
    GeometricPrimitive represents a single geometric shape in a scene (e.g., Sphere, Cone, etc.)
    all GeometricPrimitives hold a reference to a Shape and Material (which can be shared by many or no GeometricPrimitives)

    if the shape is an area light, it also hold a reference to an AreaLight
*/

#ifndef GEOMETRICPRIMITIVE_H
#define GEOMETRICPRIMITIVE_H

#include "Primitive.h"
#include "Intersection.h"

#include <memory>

#include "Shape.h"
//#include "Material.h"
//#include "AreaLight.h"

class GeometricPrimitive : public Primitive
{
public:
    // public data
    std::shared_ptr<Shape> shape;
    //std::shared_ptr<Material> material;
    //AreaLight* areaLight;

    // constructors
    GeometricPrimitive(const std::shared_ptr<Shape>& shape);
    //GeometricPrimitive(const std::shared_ptr<Shape>& shape, const std::shared_ptr<Material>& material, AreaLight* areaLight);
    
    // public functions
    virtual Bbox worldBound() const override;
    virtual bool canIntersect() const override;
    virtual bool intersects(const Ray& r, Intersection* intersection) const override;
    virtual bool intersectsP(const Ray& r) const override;
    virtual void refine(std::vector<std::shared_ptr<Primitive>>& refined) const override;

private:

};

#endif