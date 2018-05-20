#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../graphics/Window.h"
#include "../graphics/Camera.h"
#include "../graphics/Texture.h"
#include "../graphics/StaticSprite.h"


int main()
{
	Window window("3D-Engine", 960, 540);
	Shader shader("shaders/SimpleVertexShader.vertexshader", "shaders/SimpleFragmentShader.fragmentshader");
	shader.enable();

//========================================================================
// Create Camera Object (singular entity)
//========================================================================

	const int projection_Width = 4;
	const int projection_Height = 3;
	const float FOV = 45.0f;
	const float cameraX = 0;
	const float cameraY = 2;
	const float cameraZ = 5;
	//These values change with mouse-callback
	float cameraPitch = 0.0f;
	float cameraYaw = -90.0f;

	Camera camera(projection_Width, projection_Height, FOV, cameraX, cameraY, cameraZ, cameraPitch, cameraYaw);

//========================================================================
// Texturing
//========================================================================

	Texture crateTexture("textures/crate.bmp");

//========================================================================
// Create MVP's for Sprite objects (pass in camera object)
//========================================================================

	glm::vec4 colors(1, 1, 1, 1);

	StaticSprite sprite1(1, 0, -1, 2, 2, 2, &crateTexture, shader);

	StaticSprite sprite2(-3, -1, -1, 2, 2, 2, colors, shader);

//========================================================================
// Global vars for update loop
//========================================================================

	auto lastTime = glfwGetTime();
	auto nbFrames = 0;
	auto FPSToggle = false;

	auto deltaTime = 0.0f;	// Time between current frame and last frame
	auto lastFrame = 0.0f; // Time of last frame

	double mouseX = 0;
	double mouseY = 0;
	window.getMousePosition(mouseX, mouseY);
	double lastX = 0;
	double lastY = 0;
	window.getMousePosition(lastX, lastY);
	auto mouseSensitivity = 0.05f;

	while (!window.closed() && (!window.isKeyPressed(GLFW_KEY_ESCAPE)))
	{
		window.clear();

		glm::mat4 Model = glm::translate(glm::mat4(), *sprite1.getPosition());
		shader.setUniformMat4("MVP", camera.getMV() * Model);

//========================================================================
// Keyboard input for Camera Motion
//========================================================================
		glm::vec3 currentFront = camera.getFront();
		glm::vec3 currentUp = camera.getUp();
		glm::vec3 cameraPos = camera.getPos();
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		float cameraSpeed = 2.5f * deltaTime;

		//Speed boost
		bool LShiftpressed = window.isKeyPressed(GLFW_KEY_LEFT_SHIFT);
		if (LShiftpressed == GL_TRUE)
		{
			cameraSpeed = 7.5f * deltaTime;
		}
		//forwards
		bool Wpressed = window.isKeyPressed(GLFW_KEY_W);
		if (Wpressed == GL_TRUE) 
		{
			cameraPos += cameraSpeed * currentFront;
		}
		//backwards
		bool Spressed = window.isKeyPressed(GLFW_KEY_S);
		if (Spressed == GL_TRUE) 
		{
			cameraPos -= cameraSpeed * currentFront;
		}
		//left
		bool Apressed = window.isKeyPressed(GLFW_KEY_A);
		if (Apressed == GL_TRUE) 
		{
			cameraPos -= glm::normalize(glm::cross(currentFront, currentUp)) * cameraSpeed;
		}
		
		//right
		bool Dpressed = window.isKeyPressed(GLFW_KEY_D);
		if (Dpressed == GL_TRUE) 
		{
			cameraPos += glm::normalize(glm::cross(currentFront, currentUp)) * cameraSpeed;
		}
		
		//down
		bool Qpressed = window.isKeyPressed(GLFW_KEY_Q);
		if (Qpressed == GL_TRUE) 
		{
			 cameraPos.y -= cameraSpeed;
		}
		//up
		bool Epressed = window.isKeyPressed(GLFW_KEY_E);
		if (Epressed == GL_TRUE) 
		{
			cameraPos.y += cameraSpeed;
		}
		

//========================================================================
// Mouse Controller
//========================================================================		
		float xoffset = mouseX - lastX;
		float yoffset = lastY - mouseY;
		lastX = mouseX;
		lastY = mouseY;
		window.getMousePosition(mouseX, mouseY);
		xoffset *= mouseSensitivity;
		yoffset *= mouseSensitivity;

		cameraYaw += xoffset;
		cameraPitch += yoffset;

		//Update all camera values
		camera.updatePos(cameraPos.x, cameraPos.y, cameraPos.z, cameraPitch, cameraYaw);
//========================================================================
// FPS Toggler
//========================================================================
		//Equals to enable FPS
		if (window.isKeyPressed(GLFW_KEY_EQUAL) && window.isKeyPressed(GLFW_KEY_RIGHT_SHIFT))
		{
			FPSToggle = true;
			lastTime = glfwGetTime();
		}
		//Underscore to disable FPS
		if (window.isKeyPressed(GLFW_KEY_MINUS) && window.isKeyPressed(GLFW_KEY_RIGHT_SHIFT))
		{
			FPSToggle = false; 
		}

		if (FPSToggle)
		{
			// Measure speed
			double currentTime = glfwGetTime();
			nbFrames++;
			if (currentTime - lastTime >= 1.0)
			{   // If last prinf() was more than 1 sec ago
				// printf and reset timer
				printf("%f ms/frame\n", 1000.0 / double(nbFrames));
				nbFrames = 0;
				lastTime += 1.0;
			}
		}

//========================================================================
// Draw Two cubes with same data (but different model coords)
//========================================================================


		sprite1.bindArrays();

		Model = glm::translate(glm::mat4(), *sprite1.getPosition());
		shader.setUniformMat4("MVP", camera.getMV() * Model);

		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		sprite2.bindArrays();

		Model = glm::translate(glm::mat4(), *sprite2.getPosition());
		shader.setUniformMat4("MVP", camera.getMV() * Model);

		glDrawElements(GL_TRIANGLES, sprite2.getIBO()->getCount(), GL_UNSIGNED_SHORT, 0);

		window.update();
	}
	shader.~Shader();
	crateTexture.~Texture();
	
	return 0;


}


