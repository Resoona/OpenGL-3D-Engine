#pragma once

#include "../graphics/Window.h"
#include "../graphics/Camera.h"

class InputHandler
{
private:
	Window& m_Window;
public:
	InputHandler(Window& window);
	void SetWindow(Window& window);
	void Listen(Camera& camera, glm::vec3& cameraPos, float cameraSpeed, bool& FPSToggle, float& lasttime);
};
