#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../graphics/window.h"
#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../graphics/buffers/vertexarray.h"
#include "../graphics/model.h"


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
// Create MVP's for Sprite objects (pass in camera object)
//========================================================================
	int sprite1x = 1;
	int sprite1y = 0;
	int sprite1z = -1;
	Model sprite1Model(camera, sprite1x, sprite1y, sprite1z);
	int sprite2x = -2;
	int sprite2y = 0;
	int sprite2z = -1;
	Model sprite2Model(camera, sprite2x, sprite2y, sprite2z);

//========================================================================
// Texturing
//========================================================================

	GLuint Texture = loadBMP_custom("textures/crate.bmp");
	GLuint TextureID = glGetUniformLocation(shader.getShaderID(), "myTextureSampler");

//========================================================================
// Vertex Data
//========================================================================


	//Cube Data
	GLfloat g_vertex_buffer_data[] = {
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
	};

	GLfloat g_uv_buffer_data[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f
	};

	VertexArray sprite1;

	sprite1.addBuffer(new Buffer(g_vertex_buffer_data, 36 * 3, 3), 0);
	sprite1.addBuffer(new Buffer(g_uv_buffer_data, 36* 2, 2), 1);

//========================================================================
// Global vars for update loop
//========================================================================

	double lastTime = glfwGetTime();
	int nbFrames = 0;
	bool FPSToggle = false;

	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame

	double mouseX = 0;
	double mouseY = 0;
	window.getMousePosition(mouseX, mouseY);
	double lastX = 0;
	double lastY = 0;
	window.getMousePosition(lastX, lastY);
	float mouseSensitivity = 0.05f;

	while (!window.closed() && (!window.isKeyPressed(GLFW_KEY_ESCAPE)))
	{
		window.clear();
		shader.setUniformMat4("MVP", sprite1Model.getMVP(camera));

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
		sprite1.bind();

		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		shader.setUniformMat4("MVP", sprite2Model.getMVP(camera));

		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);


		window.update();
	}
	shader.~Shader();
	glDeleteTextures(1, &Texture);
	sprite1.~VertexArray();
	
	return 0;


}


