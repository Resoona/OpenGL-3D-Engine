#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../graphics/window.h"
#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../graphics/buffers/vertexarray.h"
#include "../graphics/buffers/buffer.h"


using namespace std;

int main()
{
	
	Window window("3D-Engine", 960, 540);
	Shader shader("shaders/SimpleVertexShader.vertexshader", "shaders/SimpleFragmentShader.fragmentshader");
	shader.enable();

	//========================================================================
	// Matrix for transformations
	//========================================================================

	float projection_Width = 4.0f;
	float projection_Height = 3.0f;

	//Projection matrix: 45% field of view, 4:3 aspect ratio, display range: 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)projection_Width / (float)projection_Height, 0.1f, 100.0f);

	//Camera Matrix
	glm::mat4 View = glm::lookAt(glm::vec3(1, 3, 5), //Camera pos is at (4,3,3) in world space
	glm::vec3(0, 0, 0), //and looks at the origin
	glm::vec3(0, 1, 0)); //Y is upwards

	//Matrix Model: an identity matrix (model will be at the origin)
	glm::mat4 spriteModel1 = glm::translate(glm::mat4(), glm::vec3(1.0f, 0.0f, -1.0f));
	glm::mat4 spriteModel2 = glm::translate(glm::mat4(), glm::vec3(-2.0f, 0.0f, -1.0f));
	//glm::mat4 TriangleModel = glm::mat4(1.0f);


	//Matrix Multiplication
	glm::mat4 MVP = Projection * View * spriteModel1;
	glm::mat4 MVP2 = Projection * View * spriteModel2;


	//========================================================================
	// Texturing
	//========================================================================

	GLuint Texture = loadBMP_custom("textures/uvtemplate.bmp");
	GLuint TextureID = glGetUniformLocation(shader.getShaderID(), "myTextureSampler");


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

	

	double lastTime = glfwGetTime();
	int nbFrames = 0;
	bool FPSToggle = false;

	while (!window.closed() && (!window.isKeyPressed(GLFW_KEY_ESCAPE)))
	{
		window.clear();
		shader.setUniformMat4("MVP", MVP);

		bool Apressed = window.isKeyPressed(GLFW_KEY_A);
		if (Apressed == GL_TRUE) { std::cout << "a is being pressed" << std::endl; }
		bool Spressed = window.isKeyPressed(GLFW_KEY_S);
		if (Spressed == GL_TRUE) { std::cout << "s is being pressed" << std::endl; }
		bool Dpressed = window.isKeyPressed(GLFW_KEY_D);
		if (Dpressed == GL_TRUE) { std::cout << "d is being pressed" << std::endl; }
		bool Wpressed = window.isKeyPressed(GLFW_KEY_W);
		if (Wpressed == GL_TRUE) { std::cout << "w is being pressed" << std::endl; }
		

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

		sprite1.bind();

		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		shader.setUniformMat4("MVP", MVP2);

		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);


		window.update();
	}
	shader.~Shader();
	glDeleteTextures(1, &Texture);
	sprite1.~VertexArray();
	
	return 0;


}

