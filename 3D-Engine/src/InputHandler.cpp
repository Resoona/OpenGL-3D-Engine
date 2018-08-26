#include "InputHandler.h"

InputHandler::InputHandler(Window* window, Camera* camera)
	: m_Window(window), m_Camera(camera)
{
	window->GetMousePosition(m_MouseX, m_MouseY);
	window->GetMousePosition(m_LastMouseX, m_LastMouseY);
}


void InputHandler::Listen()
{
	const float currentFrame = (float)glfwGetTime();
	const float deltaTime = currentFrame - m_LastFrame;
	m_LastFrame = currentFrame;
	float cameraSpeed = 2.5f * deltaTime;

	glm::vec3 currentFront = m_Camera->GetFront();
	glm::vec3 currentUp = m_Camera->GetUp();
	glm::vec3 cameraPos = m_Camera->GetPos();
	

	bool LShiftpressed = m_Window->IsKeyPressed(GLFW_KEY_LEFT_SHIFT);
	if (LShiftpressed == GL_TRUE)
	{
		cameraSpeed = cameraSpeed * 3;
	}
	//forwards
	bool Wpressed = m_Window->IsKeyPressed(GLFW_KEY_W);
	if (Wpressed == GL_TRUE)
	{
		cameraPos += cameraSpeed * currentFront;
		
	}
	//backwards
	bool Spressed = m_Window->IsKeyPressed(GLFW_KEY_S);
	if (Spressed == GL_TRUE)
	{
		cameraPos -= cameraSpeed * currentFront;
	}
	//left
	bool Apressed = m_Window->IsKeyPressed(GLFW_KEY_A);
	if (Apressed == GL_TRUE)
	{
		cameraPos -= glm::normalize(glm::cross(currentFront, currentUp)) * cameraSpeed;
	}

	//right
	bool Dpressed = m_Window->IsKeyPressed(GLFW_KEY_D);
	if (Dpressed == GL_TRUE)
	{
		cameraPos += glm::normalize(glm::cross(currentFront, currentUp)) * cameraSpeed;
	}

	//down
	bool Qpressed = m_Window->IsKeyPressed(GLFW_KEY_Q);
	if (Qpressed == GL_TRUE)
	{
		cameraPos.y -= cameraSpeed;
	}
	//up
	bool Epressed = m_Window->IsKeyPressed(GLFW_KEY_E);
	if (Epressed == GL_TRUE)
	{
		cameraPos.y += cameraSpeed;
	}

	if (m_Window->IsKeyPressed(GLFW_KEY_EQUAL) && m_Window->IsKeyPressed(GLFW_KEY_RIGHT_SHIFT))
	{
		FPSToggle = true;
		m_LastTime = (float)glfwGetTime();
	}
	//Underscore to disable FPS
	if (m_Window->IsKeyPressed(GLFW_KEY_MINUS) && m_Window->IsKeyPressed(GLFW_KEY_RIGHT_SHIFT))
	{
		FPSToggle = false;
	}
	

	float xoffset = (float)(m_MouseX - m_LastMouseX);
	float yoffset = (float)(m_LastMouseY - m_MouseY);
	m_LastMouseX = m_MouseX;
	m_LastMouseY = m_MouseY;
	m_Window->GetMousePosition(m_MouseX, m_MouseY);
	xoffset *= m_MouseSensitivity;
	yoffset *= m_MouseSensitivity;

	float cameraYaw = m_Camera->GetYaw() + xoffset;
	float cameraPitch = m_Camera->GetPitch() + yoffset;

	m_Camera->UpdatePos(cameraPos.x, cameraPos.y, cameraPos.z, cameraPitch, cameraYaw);

	PrintFPS();
}

void InputHandler::PrintFPS()
{
	if (FPSToggle)
	{
		// ReSharper disable once CppLocalVariableMayBeConst
		double currentTime = glfwGetTime();
		m_NumberOfFrames++;
		if (currentTime - m_LastTime >= 1.0)
		{   // If last prinf() was more than 1 sec ago
			// printf and reset timer
			printf("%f ms/frame\n", 1000.0 / double(m_NumberOfFrames));
			m_NumberOfFrames = 0.0f;
			m_LastTime += 1.0;
		}
	}
	
}


