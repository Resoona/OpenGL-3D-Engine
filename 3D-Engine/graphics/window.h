#pragma once


#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#define MAX_KEYS GLFW_KEY_LAST
#define MAX_BUTTONS GLFW_MOUSE_BUTTON_LAST

class Window
{
private:
	const char *m_Title;
	int m_Width, m_Height;
	GLFWwindow *m_Window;
	bool m_Closed;

	bool m_Keys[MAX_KEYS];
	bool m_Buttons[MAX_BUTTONS];
	double mx, my;

public:
	Window(const char *title, int width, int height);
	~Window();
	void Clear() const;
	void Update();
	bool Closed() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

	bool IsKeyPressed(unsigned int keycode) const;
	bool IsMouseButtonPressed(unsigned int button) const;
	void GetMousePosition(double& x, double& y) const;


private:
	bool Init();
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int scancode, int mods);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

};

