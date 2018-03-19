/*
 * main.cpp
 *
 *  Created on: Mar 12, 2018
 *  Author: Drew Cornfield
 *  This is a WIP.
 */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "graphics/window.h"
#include "shader.h"
#include "texture.h"
#include "graphics/buffers/buffer.h"
#include "graphics/buffers/indexbuffer.h"
#include "graphics/buffers/vertexarray.h"
#include "graphics/camera.h"

int main()
{
    Window window("OpenGL!", 960, 540);
    Shader shader("shaders/SimpleVertexShader.vertexshader", "shaders/SimpleFragmentShader.fragmentshader" );
    shader.enable();



    float projection_Width = 4.0f;
    float projection_Height = 3.0f;
    float fov =  60.0f;
    float clippingClose = 0.1f;
    float clippingFar = 100.0f;

    glm::mat4 Projection = glm::perspective(glm::radians(60.0f), (float) projection_Width / (float) projection_Height, 0.1f, 100.0f);

    //TODO
    Camera camera(Projection);






    //Camera Matrix
    glm::mat4 View = glm::lookAt(glm::vec3(1,3,3), //Camera pos is at (4,3,3) in world space
                                 glm::vec3(0,0,0), //and looks at the origin
                                 glm::vec3(0,1,0)); //Y is upwards

    //Matrix Model: an identity matrix (model will be at the origin)
    glm::mat4 spriteModel1 = glm::translate(glm::mat4(),glm::vec3(1.0f,0.0f,-1.0f));
    glm::mat4 spriteModel2 = glm::translate(glm::mat4(),glm::vec3(-2.0f,0.0f,-1.0f));
    //glm::mat4 TriangleModel = glm::mat4(1.0f);


    //Matrix Multiplication
    glm::mat4 MVP = Projection * View * spriteModel1;
    glm::mat4 MVP2 = Projection * View * spriteModel2;

    GLuint Texture = loadDDS("uvtemplate.DDS");
    GLuint TextureID  = glGetUniformLocation(shader.getShaderID(), "myTextureSampler");

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
		0.000059f, 1.0f-0.000004f,
		0.000103f, 1.0f-0.336048f,
		0.335973f, 1.0f-0.335903f,
		1.000023f, 1.0f-0.000013f,
		0.667979f, 1.0f-0.335851f,
		0.999958f, 1.0f-0.336064f,
		0.667979f, 1.0f-0.335851f,
		0.336024f, 1.0f-0.671877f,
		0.667969f, 1.0f-0.671889f,
		1.000023f, 1.0f-0.000013f,
		0.668104f, 1.0f-0.000013f,
		0.667979f, 1.0f-0.335851f,
		0.000059f, 1.0f-0.000004f,
		0.335973f, 1.0f-0.335903f,
		0.336098f, 1.0f-0.000071f,
		0.667979f, 1.0f-0.335851f,
		0.335973f, 1.0f-0.335903f,
		0.336024f, 1.0f-0.671877f,
		1.000004f, 1.0f-0.671847f,
		0.999958f, 1.0f-0.336064f,
		0.667979f, 1.0f-0.335851f,
		0.668104f, 1.0f-0.000013f,
		0.335973f, 1.0f-0.335903f,
		0.667979f, 1.0f-0.335851f,
		0.335973f, 1.0f-0.335903f,
		0.668104f, 1.0f-0.000013f,
		0.336098f, 1.0f-0.000071f,
		0.000103f, 1.0f-0.336048f,
		0.000004f, 1.0f-0.671870f,
		0.336024f, 1.0f-0.671877f,
		0.000103f, 1.0f-0.336048f,
		0.336024f, 1.0f-0.671877f,
		0.335973f, 1.0f-0.335903f,
		0.667969f, 1.0f-0.671889f,
		1.000004f, 1.0f-0.671847f,
		0.667979f, 1.0f-0.335851f
	};


    //Create a vertex array object then bind our buffers
    VertexArray sprite1;

    sprite1.addBuffer(new Buffer(g_vertex_buffer_data,36*3,3),0);
    sprite1.addBuffer(new Buffer(g_uv_buffer_data,36*2,2),1);
    double lastTime = glfwGetTime();
    int nbFrames = 0;
    bool FPSToggle = false;

    while (!window.closed() && (!window.isKeyPressed(GLFW_KEY_ESCAPE)))
    {
        window.clear();

		bool Apressed = window.isKeyPressed(GLFW_KEY_A);
		if (Apressed == GL_TRUE) {  std::cout << "a is being pressed" << std::endl; }
		bool Spressed = window.isKeyPressed(GLFW_KEY_S);
		if (Spressed == GL_TRUE) {  std::cout << "s is being pressed" << std::endl; }
		bool Dpressed = window.isKeyPressed(GLFW_KEY_D);
		if (Dpressed == GL_TRUE) {  std::cout << "d is being pressed" << std::endl; }
		bool Wpressed = window.isKeyPressed(GLFW_KEY_W);
		if (Wpressed == GL_TRUE) {  std::cout << "w is being pressed" << std::endl; }

		if (window.isKeyPressed(GLFW_KEY_EQUAL) && window.isKeyPressed(GLFW_KEY_RIGHT_SHIFT)) { FPSToggle = true; lastTime = glfwGetTime(); }
		if (window.isKeyPressed(GLFW_KEY_MINUS) && window.isKeyPressed(GLFW_KEY_RIGHT_SHIFT)) { FPSToggle = false; }

        // Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);


        sprite1.bind();

        shader.setUniformMat4("MVP",MVP); //Shift to Right

        glDrawArrays(GL_TRIANGLES,0,12*3);

        shader.setUniformMat4("MVP",MVP2); //Shift to Left

        glDrawArrays(GL_TRIANGLES,0,12*3);



        if (FPSToggle){
            // Measure speed
            double currentTime = glfwGetTime();
            nbFrames++;
            if (currentTime - lastTime >= 1.0)
            {   // If last prinf() was more than 1 sec ago
                // printf and reset timer
                printf("%f ms/frame\n", 1000.0/double(nbFrames));
                nbFrames = 0;
                lastTime += 1.0;
            }
        }

        sprite1.unbind();

		window.update();

    }


    // Cleanup VBO and shader
	shader.~Shader();
	glDeleteTextures(1, &Texture);
	sprite1.~VertexArray();


}




