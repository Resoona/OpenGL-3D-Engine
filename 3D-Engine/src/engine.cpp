#include <iostream>

#include "../graphics/Texture.h"
#include "../graphics/StaticSprite.h"
#include "../src/InputHandler.h"
#include "../renderer/Renderer.h"


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

	Texture crateTexture("textures/crate.bmp");

	glm::vec4 colors(1, 1, 1, 1);

	const StaticSprite sprite1(1, 0, -1, 2, 2, 2, &crateTexture, shader);

	const StaticSprite sprite2(-4, -1, -1, 2, 2, 2, colors, shader);

	Renderer renderer;

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

	InputHandler inputHandler(window);

	while (!window.closed() && (!window.isKeyPressed(GLFW_KEY_ESCAPE)))
	{
		window.clear();

		glm::mat4 Model = glm::translate(glm::mat4(), *sprite1.getPosition());
		//shader.setUniformMat4("MVP", camera.getMV() * Model);

		auto currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		float cameraSpeed = 2.5f * deltaTime;
		glm::vec3 cameraPos = camera.getPos();

		//Callback - modifies values of cameraPos & FPSToggle
		inputHandler.listen(camera, cameraPos, cameraSpeed, FPSToggle);

//========================================================================
// Mouse Controller
//========================================================================		
		auto xoffset = mouseX - lastX;
		auto yoffset = lastY - mouseY;
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
		if (FPSToggle)
		{
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
		shader.setUniformMat4("VP", camera.getVP());
		
		renderer.submit(&sprite1);
		renderer.submit(&sprite2);
		renderer.flush();

		window.update();
	}
	shader.~Shader();
	crateTexture.~Texture();
	
	return 0;


}


