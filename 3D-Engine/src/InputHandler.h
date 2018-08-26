#pragma once

#include "../graphics/Window.h"
#include "../graphics/Camera.h"

class InputHandler
{
private:
	Window* m_Window;
	Camera* m_Camera;

	bool FPSToggle = false;

	double m_MouseX = 0.0f;
	double m_MouseY = 0.0f;
	double m_LastMouseX = 0;
	double m_LastMouseY = 0;
	
	const float m_MouseSensitivity = 0.05f;
	

	float m_LastTime = (float)glfwGetTime();
	float m_NumberOfFrames = 0;
	float m_LastFrame = 0.0f; // Time of last frame

	void PrintFPS();

public:
	InputHandler(Window* window, Camera* camera);
	inline void SetWindow(Window* window) { m_Window = window; }
	inline void SetCamera(Camera* camera) { m_Camera = camera; }
	void Listen();
	
};
