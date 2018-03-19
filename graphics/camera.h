#pragma once

#include "window.h"
#include <GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>


    class Camera
    {
    private:
        Window* window;
        float m_projection_Width;
        float m_projection_Height;
        float m_renderDist_Close;
        float m_renderDist_Far;
        float m_fieldOfView;
        GLint m_camera_xpos;
        GLint m_camera_ypos;
        GLint m_camera_zpos;
        glm::mat4 m_projection;
        glm::mat4 m_view;
    public:
        Camera(Window* window, float projection_Width, float projections_Height, float renderDist_Close, float renderDist_Far, float fov, GLint posx, GLint posy, GLint posz);
        void updateProjectionMatrix(float projection_Width, float projection_Height, float, float renderDist_Close, float renderDist_Far, float fov);
        void updateViewMatrix(GLint posx, GLint posy, GLint posz);

    };
