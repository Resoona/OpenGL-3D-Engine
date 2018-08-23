#include "InputHandler.h"

InputHandler::InputHandler(Window& window)
	: m_Window(window)
{
}

void InputHandler::SetWindow(Window& window)
{
	m_Window = window;
}

void InputHandler::Listen(Camera& camera, glm::vec3& cameraPos, float cameraSpeed, bool& FPSToggle, float& lasttime)
{
	glm::vec3 currentFront = camera.GetFront();
	glm::vec3 currentUp = camera.GetUp();
	

	bool LShiftpressed = m_Window.IsKeyPressed(GLFW_KEY_LEFT_SHIFT);
	if (LShiftpressed == GL_TRUE)
	{
		cameraSpeed = cameraSpeed * 3;
	}
	//forwards
	bool Wpressed = m_Window.IsKeyPressed(GLFW_KEY_W);
	if (Wpressed == GL_TRUE)
	{
		cameraPos += cameraSpeed * currentFront;
	}
	//backwards
	bool Spressed = m_Window.IsKeyPressed(GLFW_KEY_S);
	if (Spressed == GL_TRUE)
	{
		cameraPos -= cameraSpeed * currentFront;
	}
	//left
	bool Apressed = m_Window.IsKeyPressed(GLFW_KEY_A);
	if (Apressed == GL_TRUE)
	{
		cameraPos -= glm::normalize(glm::cross(currentFront, currentUp)) * cameraSpeed;
	}

	//right
	bool Dpressed = m_Window.IsKeyPressed(GLFW_KEY_D);
	if (Dpressed == GL_TRUE)
	{
		cameraPos += glm::normalize(glm::cross(currentFront, currentUp)) * cameraSpeed;
	}

	//down
	bool Qpressed = m_Window.IsKeyPressed(GLFW_KEY_Q);
	if (Qpressed == GL_TRUE)
	{
		cameraPos.y -= cameraSpeed;
	}
	//up
	bool Epressed = m_Window.IsKeyPressed(GLFW_KEY_E);
	if (Epressed == GL_TRUE)
	{
		cameraPos.y += cameraSpeed;
	}

	if (m_Window.IsKeyPressed(GLFW_KEY_EQUAL) && m_Window.IsKeyPressed(GLFW_KEY_RIGHT_SHIFT))
	{
		FPSToggle = true;
		lasttime = (float)glfwGetTime();
	}
	//Underscore to disable FPS
	if (m_Window.IsKeyPressed(GLFW_KEY_MINUS) && m_Window.IsKeyPressed(GLFW_KEY_RIGHT_SHIFT))
	{
		FPSToggle = false;
	}
}
