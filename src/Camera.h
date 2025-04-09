#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "globals.h"

class Camera {
    public:
        Camera();
        
        // getters
        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjMatrix() const;

        glm::vec3 getPosition() const;
        
        // setters 
        void setPosition(const glm::vec3 &position);
        
    private:
        glm::vec3 m_position;
        glm::vec3 m_target;
        glm::vec3 m_up;
        float m_fov;
        float m_aspectRatio;
        float m_zNear;
        float m_zFar;
        
        mutable glm::mat4 m_viewMatrix;
        mutable glm::mat4 m_projMatrix;
        
        void updateMatrices() const;
};

#endif