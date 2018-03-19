#include "camera.h"

    Camera::Camera(glm:mat4& projectionMatrix)
            m_Projection = projectionMatrix
    {
        m_ViewMatrix = glm::mat4();
        m_Position = glm::vec3();
        m_Rotation = glm::vec3();
    }


