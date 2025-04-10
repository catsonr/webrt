#ifndef CAMERA_H
#define CAMERA_H

#include "globals.h"
#include "Vector.h"
#include "Point.h"

class Camera
{
public:
    Camera();

    virtual float generateRay() const = 0;

private:
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