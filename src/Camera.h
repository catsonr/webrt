#ifndef CAMERA_H
#define CAMERA_H

#include "globals.h"
#include "Vector.h"
#include "Point.h"

class Camera
{
public:
    Camera();

    // virtual functions
    virtual float generateRay() const = 0;

    // getters
    // glm::mat4 getViewMatrix() const;
    // glm::mat4 getProjMatrix() const;
    Point getPosition() const;

    // setters
    void setPosition(Point &p);

private:
    Point position;
    Point target;
    Vector up;
    float fov;
    float aspectRatio;
    float clipNear;
    float clipFar;

    // mutable glm::mat4 viewMatrix;
    // mutable glm::mat4 projMatrix;

    void updateMatrices() const;
};

#endif