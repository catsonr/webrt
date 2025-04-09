#include "Camera.h"

Camera::Camera() :
    m_position(0.0f, 0.0f, -0.5f),
    m_target(0.0f, 0.0f, 0.0f),
    m_up(0.0f, 1.0f, 0.0f),
    m_fov(45.0f * PI / 180.0f),
    m_aspectRatio((float)CANVAS_WIDTH / (float)CANVAS_HEIGHT),
    m_clipNear(0.1f),
    m_clipFar(100.0f)
{
    // initialize matrices
}

// getters
glm::mat4 Camera::getViewMatrix() const 
{
    return m_viewMatrix;
}
glm::mat4 Camera::getProjMatrix() const 
{
    return m_projMatrix;
}
glm::vec3 Camera::getPosition() const 
{
    return m_position;
}

// setters
void Camera::setPosition(const glm::vec3 &position) 
{
    m_position = position;
}

// private functions
void Camera::updateMatrices() const 
{

}