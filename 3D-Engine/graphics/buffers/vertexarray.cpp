#include "VertexArray.h"
#include <iostream>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_ArrayID);
}

VertexArray::~VertexArray()
{
	for (int i = 0; i < m_Buffers.size(); i++)
	{
		delete m_Buffers[i];
	}
}

void VertexArray::addBuffer(Buffer* buffer, GLuint index)
{
	bind();
	buffer->bind();

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, (void*)0);

	buffer->unbind();
	unbind();
}

void VertexArray::PushBuffer(Buffer* buffer)
{

	m_Buffers.push_back(buffer);

	const std::vector<BufferLayoutType>& layout = buffer->layout.GetLayout();
	for (uint i = 0; i < layout.size(); i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, layout[i].count, layout[i].type, (uint)layout[i].normalized, buffer->layout.GetStride(), (const GLvoid*)layout[i].offset);
	}
}


void VertexArray::bind() const
{
	glBindVertexArray(m_ArrayID);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::Draw(GLuint count) const
{
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, nullptr);
}