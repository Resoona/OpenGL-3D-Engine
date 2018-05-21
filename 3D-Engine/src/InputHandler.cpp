#include "InputHandler.h"

InputHandler::InputHandler(Window& window)
	: m_Window(window)
{
}

void InputHandler::setWindow(Window& window)
{
	m_Window = window;
}

void InputHandler::listen(Camera& camera, glm::vec3& cameraPos, float cameraSpeed, bool& FPSToggle)
{
	glm::vec3 currentFront = camera.getFront();
	glm::vec3 currentUp = camera.getUp();
	

	bool LShiftpressed = m_Window.isKeyPressed(GLFW_KEY_LEFT_SHIFT);
	if (LShiftpressed == GL_TRUE)
	{
		cameraSpeed = cameraSpeed * 3;
	}
	//forwards
	bool Wpressed = m_Window.isKeyPressed(GLFW_KEY_W);
	if (Wpressed == GL_TRUE)
	{
		cameraPos += cameraSpeed * currentFront;
	}
	//backwards
	bool Spressed = m_Window.isKeyPressed(GLFW_KEY_S);
	if (Spressed == GL_TRUE)
	{
		cameraPos -= cameraSpeed * currentFront;
	}
	//left
	bool Apressed = m_Window.isKeyPressed(GLFW_KEY_A);
	if (Apressed == GL_TRUE)
	{
		cameraPos -= glm::normalize(glm::cross(currentFront, currentUp)) * cameraSpeed;
	}

	//right
	bool Dpressed = m_Window.isKeyPressed(GLFW_KEY_D);
	if (Dpressed == GL_TRUE)
	{
		cameraPos += glm::normalize(glm::cross(currentFront, currentUp)) * cameraSpeed;
	}

	//down
	bool Qpressed = m_Window.isKeyPressed(GLFW_KEY_Q);
	if (Qpressed == GL_TRUE)
	{
		cameraPos.y -= cameraSpeed;
	}
	//up
	bool Epressed = m_Window.isKeyPressed(GLFW_KEY_E);
	if (Epressed == GL_TRUE)
	{
		cameraPos.y += cameraSpeed;
	}

	if (m_Window.isKeyPressed(GLFW_KEY_EQUAL) && m_Window.isKeyPressed(GLFW_KEY_RIGHT_SHIFT))
	{
		FPSToggle = true;
	}
	//Underscore to disable FPS
	if (m_Window.isKeyPressed(GLFW_KEY_MINUS) && m_Window.isKeyPressed(GLFW_KEY_RIGHT_SHIFT))
	{
		FPSToggle = false;
	}
}
