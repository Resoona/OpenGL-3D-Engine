/*
 * main.cpp
 *
 *  Created on: Mar 12, 2018
 *      Author: drew
 */


#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "shader.h"
#include "texture.h"

int main()
{
    if (!glfwInit())
    {
        fprintf(stderr,"Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    //Creating our main window
    GLFWwindow* window;

    window = glfwCreateWindow(1024,768,"Application", NULL,NULL);
    if (window == NULL)
    {
        fprintf(stderr,"Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewExperimental=true;
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);

    //Create a vertex array object and bind it
    unsigned int VertexArrayID;
    glGenVertexArrays(1,&VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint programID = LoadShaders( "shaders/SimpleVertexShader.vertexshader", "shaders/SimpleFragmentShader.fragmentshader" );


    unsigned int MatrixID = glGetUniformLocation(programID, "MVP");

    float width = 4.0f;
    float height = 3.0f;


    //Projection matrix: 45% field of view, 4:3 aspect ratio, display range: 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(glm::radians(60.0f), (float) width / (float) height, 0.1f, 100.0f);


    //Camera Matrix
    glm::mat4 View = glm::lookAt(glm::vec3(-1.5,0,0), //Camera pos is at (4,3,3) in world space
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
    GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");



    //Cube Data
    static const GLfloat g_vertex_buffer_data[] = {
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

    static const GLfloat g_uv_buffer_data[] = {
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

//    static GLfloat g_color_buffer_data[12*3*3];
//    static GLfloat g_color_buffer2_data[12*3*3];


//    for (int v = 0; v < 12*3*3 ; v++){
//       g_color_buffer_data[v+0] = (float)(rand() % 2);
//       g_color_buffer_data[v+1] = (float)(rand() % 2);
//       g_color_buffer_data[v+2] = (float)(rand() % 2);
//       g_color_buffer2_data[v+0] = (float)(rand() % 2);
//       g_color_buffer2_data[v+1] = (float)(rand() % 2);
//       g_color_buffer2_data[v+2] = (float)(rand() % 2);
//    }
    //create a vertex buffer and pass in our data for openGL
    unsigned int vertexBuffer;
    glGenBuffers(1,&vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(g_vertex_buffer_data),g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint uvBuffer;
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);



      //Colour Buffers
//    unsigned int colorBuffer;
//    glGenBuffers(1,&colorBuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);


//    //Colour Buffers
//    unsigned int colorBuffer2;
//    glGenBuffers(1,&colorBuffer2);
//    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer2);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(g_color_buffer2_data), g_color_buffer2_data, GL_STATIC_DRAW);
//

    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programID);

        glUniformMatrix4fv(MatrixID,1,GL_FALSE,&MVP[0][0]);

        // Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
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
        glBindBuffer(GL_ARRAY_BUFFER,uvBuffer);
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


        glUniformMatrix4fv(MatrixID,1,GL_FALSE,&MVP2[0][0]);

//        glEnableVertexAttribArray(3);
//        glBindBuffer(GL_ARRAY_BUFFER,colorBuffer2);
//        glVertexAttribPointer
//        (
//        3,                 // attribute 0, no real reason for 1, but must match the layout in the shader.
//        3,                 // size
//        GL_FLOAT,          // type
//        GL_FALSE,          // normalized?
//        0,                 // array buffer offset
//        (void*)0
//        );

        glDrawArrays(GL_TRIANGLES,0,12*3);

        glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    while (
        glfwGetKey(window,GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0
    );

    // Cleanup VBO and shader
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &uvBuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);


}




