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

int main()
{
    Window window("OpenGL!", 960, 540);
    Shader shader("shaders/SimpleVertexShader.vertexshader", "shaders/SimpleFragmentShader.fragmentshader" );
    shader.enable();
    //unsigned int MatrixID = shader.getUniformLocation("MVP");


    //Create a vertex array object and bind it
    unsigned int VertexArrayID;
    glGenVertexArrays(1,&VertexArrayID);
    glBindVertexArray(VertexArrayID);

    float projection_Width = 4.0f;
    float projection_Height = 3.0f;


    //Projection matrix: 45% field of view, 4:3 aspect ratio, display range: 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(glm::radians(60.0f), (float) projection_Width / (float) projection_Height, 0.1f, 100.0f);


    //Camera Matrix
    glm::mat4 View = glm::lookAt(glm::vec3(1,3,3), //Camera pos is at (4,3,3) in world space
                                 glm::vec3(0,0,0), //and looks at the origin
                                 glm::vec3(0,1,0)); //Y is upwards

    //Matrix Model: an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::translate(glm::mat4(),glm::vec3(1.0f,0.0f,-1.0f));
    glm::mat4 Model2 = glm::translate(glm::mat4(),glm::vec3(-2.0f,0.0f,-1.0f));
    //glm::mat4 TriangleModel = glm::mat4(1.0f);


    //Matrix Multiplication
    glm::mat4 MVP = Projection * View * Model;
    glm::mat4 MVP2 = Projection * View * Model2;

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

    Buffer vertexBuffer(g_vertex_buffer_data,36*3,3);
    //buffer.bind();
    //GLuint vertexBuffer;
    //glGenBuffers(1,&vertexBuffer);
    //glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    //glBufferData(GL_ARRAY_BUFFER,sizeof(g_vertex_buffer_data),g_vertex_buffer_data, GL_STATIC_DRAW);

    Buffer uvBuffer(g_uv_buffer_data,36*2,2);
    //GLuint uvBuffer;
	//glGenBuffers(1, &uvBuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);



    while (!window.closed() && (!window.isKeyPressed(GLFW_KEY_ESCAPE)))
    {
        window.clear();

		bool pressed = window.isKeyPressed(GLFW_KEY_A);
		if (pressed == GL_TRUE) {
        std::cout << "a is being pressed" << std::endl;
		}

		shader.setUniformMat4("MVP",MVP);

        // Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);

        glEnableVertexAttribArray(0);
        //glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
        vertexBuffer.bind();
        glVertexAttribPointer
        (
        0,                 // attribute 0, no real reason for 0, but must match the layout in the shader.
        3,                 // size
        GL_FLOAT,          // type
        GL_FALSE,          // normalized?
        0,                 // array buffer offset
        (void*)0
        );

        glEnableVertexAttribArray(1);
        //glBindBuffer(GL_ARRAY_BUFFER,uvBuffer);
        uvBuffer.bind();
        glVertexAttribPointer
        (
        1,                 // attribute 0, no real reason for 1, but must match the layout in the shader.
        2,                 // size
        GL_FLOAT,          // type
        GL_FALSE,          // normalized?
        0,                 // array buffer offset
        (void*)0
        );

        glDrawArrays(GL_TRIANGLES,0,12*3);

        shader.setUniformMat4("MVP",MVP2);

        glDrawArrays(GL_TRIANGLES,0,12*3);

        glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		window.update();

    }


    // Cleanup VBO and shader
	//glDeleteBuffers(1, &vertexBuffer);
	//glDeleteBuffers(1, &uvBuffer);
	shader.~Shader();
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);


}




