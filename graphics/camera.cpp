
#include "camera.h"

Camera::Camera(Window* window, float projection_Width, float projections_Height, float renderDist_Close, float renderDist_Far, float fov, GLint posx, GLint posy, GLint posz)
{
    m_projection = glm::perspective(glm::radians(fov), (float) projection_Width / (float) projection_Height, renderDist_Close, renderDist_Far);
}

