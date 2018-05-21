#pragma once

#include "../graphics/Window.h"
#include "../graphics/Camera.h"

class InputHandler
{
private:
	Window& m_Window;
public:
	InputHandler(Window& window);
	void setWindow(Window& window);
	void listen(Camera& camera, glm::vec3& cameraPos, float cameraSpeed, bool& FPSToggle);
};
