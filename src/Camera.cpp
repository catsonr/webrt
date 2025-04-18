#include "Camera.h"

Camera::Camera() :
    position(0.0f, 0.0f, -0.5f),
    target(0.0f, 0.0f, 0.0f),
    up(0.0f, 1.0f, 0.0f),
    fov(45.0f * rt::PI / 180.0f),
    aspectRatio((float)rt::CANVAS_WIDTH / (float)rt::CANVAS_HEIGHT),
    clipNear(0.1f),
    clipFar(100.0f)
{}