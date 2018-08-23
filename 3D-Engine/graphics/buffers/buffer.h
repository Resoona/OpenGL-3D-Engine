#pragma once
#include <GL/glew.h>
#include "BufferLayout.h"


class Buffer
{
private:
	GLuint m_BufferID;
	GLuint m_ComponentCount;
	GLuint target;
	GLuint usage;
	GLuint size;
	

public:
	BufferLayout layout;
	Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
	Buffer(GLuint target, GLuint usage);


	void Bind() const;
	void Unbind() const;
	void SetData(GLuint size, const void* data);

	inline GLuint getComponentCount() const { return m_ComponentCount; }


};
