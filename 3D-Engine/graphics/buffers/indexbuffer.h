#pragma once
#include <GL/glew.h>

class IndexBuffer
{

private:
	GLuint m_BufferID;
	GLuint m_Count;
public:
	IndexBuffer(GLushort* data, GLsizei count);
	IndexBuffer(GLuint* data, GLsizei count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline GLuint getCount() const { return m_Count; }

};



