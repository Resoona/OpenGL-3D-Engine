#pragma once

#include <vector>
#include <GL/glew.h>

#include "Buffer.h"

class VertexArray
{
private:
	GLuint m_ArrayID;
	std::vector<Buffer*> m_Buffers;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(Buffer* buffer, GLuint index);
	void Bind() const;
	void Unbind() const;
	void VertexArray::Draw(GLuint count) const;
	void PushBuffer(Buffer* buffer);

};
