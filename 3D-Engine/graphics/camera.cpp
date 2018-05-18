#include "camera.h"


Camera::Camera(int projWidth, int projHeight, float fov, int x, int y, int z)
	: m_projWidth(projWidth), m_projHeight(projHeight), m_fov(fov), m_x(x), m_y(y), m_z(z)
{

	m_Projection = glm::perspective(glm::radians(fov), (float)m_projWidth / (float)m_projHeight, 0.1f, 100.0f);
	m_View = glm::lookAt(glm::vec3(x, y, z), //Camera pos is at (4,3,3) in world space
				glm::vec3(0, 0, 0), //and looks at the origin
				glm::vec3(0, 1, 0)); //Y is upwards

	m_MV = m_Projection * m_View;
}

Camera::~Camera()
{
}

void Camera::update()
{
	m_Projection = glm::perspective(glm::radians(m_fov), (float)m_projWidth / (float)m_projHeight, 0.1f, 100.0f);
	m_View = glm::lookAt(glm::vec3(m_x, m_y, m_z), //Camera pos is at (4,3,3) in world space
		glm::vec3(0, 0, 0), //and looks at the origin
		glm::vec3(0, 1, 0)); //Y is upwards

	m_MV = m_Projection * m_View;

}

