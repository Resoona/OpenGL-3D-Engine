#include "StaticSprite.h"

StaticSprite::StaticSprite(float x, float y, float width, float height, const glm::vec4& color, Shader& shader)
	: m_Shader(shader)
{
	m_VertexArray = new VertexArray();

	GLfloat verticies[] =
	{
		0, 0, 0,
		0, height, 0,
		width, height, 0,
		width, 0, 0	
	};

	GLfloat colors[] =
	{
		color.x, color.y, color.z, color.w,
		color.x, color.y, color.z, color.w,
		color.x, color.y, color.z, color.w,
		color.x, color.y, color.z, color.w
	};

	GLfloat uvdata[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	GLushort indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	m_VertexArray->addBuffer(new Buffer(verticies, sizeof(verticies), 3), 0);
	m_VertexArray->addBuffer(new Buffer(uvdata, sizeof(uvdata), 2), 1);
	m_VertexArray->addBuffer(new Buffer(colors, sizeof(colors), 4), 2);

	m_IndexBuffer = new IndexBuffer(indices, 6);
}

StaticSprite::~StaticSprite()
{
	delete m_VertexArray;
	delete m_IndexBuffer;
}

void StaticSprite::bindArrays()
{
	m_VertexArray->bind();
	m_IndexBuffer->bind();
}
