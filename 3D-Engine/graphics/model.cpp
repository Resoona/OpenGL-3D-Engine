#include "model.h"



Model::Model(Camera camera, int mx, int my, int mz)
	: m_Camera(camera), m_mx(mx), m_my(my), m_mz(mz)
{
	m_Model = glm::translate(glm::mat4(), glm::vec3(m_mx, m_my, m_mz));
	m_MVP = m_Camera.getMV() * m_Model;
}

Model::~Model()
{
}


void Model::updatePos(int newx, int newy, int newz)
{
	m_mx = newx;
	m_my = newy;
	m_mz = newz;
	update();
}

glm::mat4 Model::getMVP(Camera updatedCamera)
{
	m_Camera = updatedCamera;
	m_MVP = m_Camera.getMV() * m_Model;
	return m_MVP;
}

void Model::update()
{
	m_Model = glm::translate(glm::mat4(), glm::vec3(m_mx, m_my, m_mz));
	m_MVP = m_Camera.getMV() * m_Model;
}




