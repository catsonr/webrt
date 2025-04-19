#ifndef AREALIGHT_H
#define AREALIGHT_H

#include "Light.h"

class AreaLight : public Light
{
public:
    /* CONSTRUCTORS */
    AreaLight(const Transform& light_to_world, const Spectrum& le, int ns, const std::shared_ptr<Shape>& s) :
        Light(light_to_world, ns)
    {
        Lemit = le;
        if(s->canIntersect())
            shape = s;
        else
        {
            // create shapeset for shape
            // implimentation was never provided ?
        }
        
        area = shape->area();
    }
    
    /* VIRTUAL FUNCTIONS */
    virtual Spectrum L(const Point& p, const Normal& n, const Vector& w) const
    {
        return dot(Vector(n), w) > 0 ? Lemit : 0.0f;
    }

protected:
    Spectrum Lemit;
    std::shared_ptr<Shape> shape;
    float area;
};

#endif