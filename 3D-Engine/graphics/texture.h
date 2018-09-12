#pragma once
#include <gl/glew.h>
#include "../utils/Eng.h"

class Texture
{
private:
	const char* m_imageloc;
	GLuint m_Texture;


public:
	Texture(const char* imageloc);
	~Texture();
	void Bind(uint slot = 0);
	void Unbind(uint slot = 0);

	inline GLuint getID() const { return m_Texture; }

};


#ifndef TEXTURE_H
#define TEXTURE_H

// Load a .BMP file using our custom loader
GLuint LoadBMP_custom(const char * imagepath);

//// Since GLFW 3, glfwLoadTexture2D() has been removed. You have to use another texture loading library,
//// or do it yourself (just like loadBMP_custom and loadDDS)
//// Load a .TGA file using GLFW's own loader
//GLuint loadTGA_glfw(const char * imagepath);

// Load a .DDS file using GLFW's own loader
GLuint LoadDDS(const char * imagepath);


#endif
