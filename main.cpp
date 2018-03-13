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
#include "shader.h"

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

    //Create a vertex array object and bind it
    unsigned int VertexArrayID;
    glGenVertexArrays(1,&VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint programID = LoadShaders( "shaders/SimpleVertexShader.vertexshader", "shaders/SimpleFragmentShader.fragmentshader" );


    //Triangle
    static const GLfloat g_vertex_buffer_data[] =
    {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };

    //create a vertex buffer and pass in our data for openGL
    unsigned int vertexBuffer;
    glGenBuffers(1,&vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(g_vertex_buffer_data),g_vertex_buffer_data, GL_STATIC_DRAW);

    do
    {
        glClear( GL_COLOR_BUFFER_BIT );

        glUseProgram(programID);

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
        glDrawArrays(GL_TRIANGLES,0,3);
        glDisableVertexAttribArray(0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    while (
        glfwGetKey(window,GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0
    );


}




