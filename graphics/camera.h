#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
//TODO

    class Camera
    {
    private:

        glm::tmat4x4 m_Projection;
        glm::mat4 m_View;
        glm::vec3 m_Position, m_Rotation, m_FocalPoint;
    public:
        Camera(glm::tmat4x4& projectionMatrix);

        inline const glm::vec3& GetPosition() const { return m_Position; }
        inline void SetPosition(const glm::vec3& position) { m_Position = position; }

        inline const glm::vec3& GetRotation() const { return m_Rotation; }
        inline void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; }

        inline const glm::tmat4x4& GetProjectionMatrix() const { return m_Projection; }
        inline void setProjectionMatrix(const glm::mat4& projectionMatrix) { m_Projection = projectionMatrix; }

        inline void Translate(const glm::vec3& translation) { m_Position = translation; }
        inline void Rotate(const glm::vec3& rotation) { m_Rotation = rotation; }

        inline const glm::vec3& GetFocalPoint() const { return m_FocalPoint; }

        inline const glm::mat4& getViewMatrix() const { return m_View; }



    };
