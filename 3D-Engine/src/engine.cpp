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
	int projection_Width = 4;
	int projection_Height = 3;
	float FOV = 45.0f;
	float cameraX = 0;
	float cameraY = 2;
	float cameraZ = 5;

	Camera camera(projection_Width, projection_Height, FOV, cameraX, cameraY, cameraZ);

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

	GLuint Texture = loadBMP_custom("textures/uvtemplate.bmp");
	GLuint TextureID = glGetUniformLocation(shader.getShaderID(), "myTextureSampler");


//========================================================================
// Vertex Data
//========================================================================

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//Cube Data
	GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	GLfloat g_uv_buffer_data[] = {
		0.000059f, 1.0f - 0.000004f,
		0.000103f, 1.0f - 0.336048f,
		0.335973f, 1.0f - 0.335903f,
		1.000023f, 1.0f - 0.000013f,
		0.667979f, 1.0f - 0.335851f,
		0.999958f, 1.0f - 0.336064f,
		0.667979f, 1.0f - 0.335851f,
		0.336024f, 1.0f - 0.671877f,
		0.667969f, 1.0f - 0.671889f,
		1.000023f, 1.0f - 0.000013f,
		0.668104f, 1.0f - 0.000013f,
		0.667979f, 1.0f - 0.335851f,
		0.000059f, 1.0f - 0.000004f,
		0.335973f, 1.0f - 0.335903f,
		0.336098f, 1.0f - 0.000071f,
		0.667979f, 1.0f - 0.335851f,
		0.335973f, 1.0f - 0.335903f,
		0.336024f, 1.0f - 0.671877f,
		1.000004f, 1.0f - 0.671847f,
		0.999958f, 1.0f - 0.336064f,
		0.667979f, 1.0f - 0.335851f,
		0.668104f, 1.0f - 0.000013f,
		0.335973f, 1.0f - 0.335903f,
		0.667979f, 1.0f - 0.335851f,
		0.335973f, 1.0f - 0.335903f,
		0.668104f, 1.0f - 0.000013f,
		0.336098f, 1.0f - 0.000071f,
		0.000103f, 1.0f - 0.336048f,
		0.000004f, 1.0f - 0.671870f,
		0.336024f, 1.0f - 0.671877f,
		0.000103f, 1.0f - 0.336048f,
		0.336024f, 1.0f - 0.671877f,
		0.335973f, 1.0f - 0.335903f,
		0.667969f, 1.0f - 0.671889f,
		1.000004f, 1.0f - 0.671847f,
		0.667979f, 1.0f - 0.335851f
	};

	VertexArray sprite1;

	sprite1.addBuffer(new Buffer(g_vertex_buffer_data, 36 * 3, 3), 0);
	sprite1.addBuffer(new Buffer(g_uv_buffer_data, 36 * 2, 2), 1);

//========================================================================
// Global vars for update loop
//========================================================================

	double lastTime = glfwGetTime();
	int nbFrames = 0;
	bool FPSToggle = false;

	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame

	

	while (!window.closed() && (!window.isKeyPressed(GLFW_KEY_ESCAPE)))
	{
		window.clear();
		shader.setUniformMat4("MVP", sprite1Model.getMVP(camera));

//========================================================================
// Keyboard input for Camera Motion
//========================================================================
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		float cameraSpeed = 2.5f * deltaTime;
		//left
		bool Apressed = window.isKeyPressed(GLFW_KEY_A);
		if (Apressed == GL_TRUE) {
			if (cameraX > -10) cameraX -= cameraSpeed;
		}
		//backwards
		bool Spressed = window.isKeyPressed(GLFW_KEY_S);
		if (Spressed == GL_TRUE) {
			if (cameraZ < 10) cameraZ += cameraSpeed;
		}
		//right
		bool Dpressed = window.isKeyPressed(GLFW_KEY_D);
		if (Dpressed == GL_TRUE) {
			if (cameraX < 10) cameraX += cameraSpeed;
		}
		//forwards
		bool Wpressed = window.isKeyPressed(GLFW_KEY_W);
		if (Wpressed == GL_TRUE) { 
			if (cameraZ > -10) cameraZ -= cameraSpeed;
		}
		//down
		bool Epressed = window.isKeyPressed(GLFW_KEY_E);
		if (Epressed == GL_TRUE) {
			if (cameraY > -10) cameraY -= cameraSpeed;
		}
		//up
		bool Qpressed = window.isKeyPressed(GLFW_KEY_Q);
		if (Qpressed == GL_TRUE) {
			if (cameraY < 10) cameraY += cameraSpeed;
		}
		camera.updatePos(cameraX, cameraY, cameraZ);
		camera.update();

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


