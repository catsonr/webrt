#include "Camera.h"

Camera::Camera() :
    position(0.0f, 0.0f, -0.5f),
    target(0.0f, 0.0f, 0.0f),
    up(0.0f, 1.0f, 0.0f),
    fov(45.0f * PI / 180.0f),
    aspectRatio((float)CANVAS_WIDTH / (float)CANVAS_HEIGHT),
    clipNear(0.1f),
    clipFar(100.0f)
{
    // initialize matrices
}

// getters
Point Camera::getPosition() const
{
    return position;
}

// setters
void Camera::setPosition(Point& p) 
{
    position = p;
}

// private functions
void Camera::updateMatrices() const 
{

}