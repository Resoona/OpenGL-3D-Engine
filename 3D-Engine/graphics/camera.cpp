#include "Camera.h"


Camera::Camera(int projWidth, int projHeight, float fov, float x, float y, float z, float pitch, float yaw)
	: m_projWidth(projWidth), m_projHeight(projHeight), m_fov(fov), m_pitch(pitch), m_yaw(yaw)
{

	m_pos = glm::vec3(x, y, z);

	m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front.y = sin(glm::radians(m_pitch));
	m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

	m_front = glm::normalize(m_front);

	m_up.x = 0.0f;
	m_up.y = 1.0f;
	m_up.z = 0.0f;

	m_right = glm::normalize(glm::cross(m_front, m_up));
	m_up = glm::normalize(glm::cross(m_right, m_front));

	Update();
}

Camera::~Camera()
{
}

void Camera::UpdatePos(float newx, float newy, float newz, float newpitch, float newyaw)
{
	m_pos = glm::vec3(newx, newy, newz);
	m_pitch = newpitch;
	m_yaw = newyaw;

	m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front.y = sin(glm::radians(m_pitch));
	m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

	m_front = glm::normalize(m_front);

	m_up.x = 0.0f;
	m_up.y = 1.0f;
	m_up.z = 0.0f;

	m_right = glm::normalize(glm::cross(m_front, m_up));
	m_up = glm::normalize(glm::cross(m_right, m_front));

	
	Update();
}

void Camera::Update()
{
	m_Projection = glm::perspective(glm::radians(m_fov), (float)m_projWidth / (float)m_projHeight, 0.1f, 1000.0f);
	m_View = glm::lookAt(m_pos,
		m_pos + m_front,
		m_up);

	m_VP = m_Projection * m_View;
}

