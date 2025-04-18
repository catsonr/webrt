#ifndef CAMERA_H
#define CAMERA_H

#include "globals.h"
#include "Ray.h"
#include "Sampler.h"

class Camera
{
public:
    Camera();

    virtual float generateRay(const Sample& sample, Ray* ray) const = 0;

protected:
    Point position;
    Point target;
    Vector up;
    float fov;
    float aspectRatio;
    float clipNear;
    float clipFar;

    void updateMatrices() const;
};

#endif