#include "StaticSprite.h"

StaticSprite::StaticSprite(float x, float y, float z, float width, float height, float depth, const glm::vec4& color, Shader& shader)
	: m_Shader(shader), m_textureID(0)
{
	m_VertexArray = new VertexArray();

	m_position = new glm::vec3(x, y, z);
	m_size = new glm::vec3(width, height, depth);

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

StaticSprite::StaticSprite(float x, float y, float z, float width, float height, float depth, GLuint textureID, Shader& shader)
	: m_Shader(shader), m_textureID(textureID)
{
	
	m_position = new glm::vec3(x, y, z);
	m_size = new glm::vec3(width, height, depth);


	GLfloat verticies[] = {
		-width, -height, -depth,
		 width, -height, -depth,
		 width,  height, -depth,
		 width,  height, -depth,
		-width,  height, -depth,
		-width, -height, -depth,		 
		-width, -height,  depth,
		 width, -height,  depth,
		 width,  height,  depth,
		 width,  height,  depth,
		-width,  height,  depth,
		-width, -height,  depth,		 
		-width,  height,  depth,
		-width,  height, -depth,
		-width, -height, -depth,
		-width, -height, -depth,
		-width, -height,  depth,
		-width,  height,  depth,		 
		 width,  height,  depth,
		 width,  height, -depth,
		 width, -height, -depth,
		 width, -height, -depth,
		 width, -height,  depth,
		 width,  height,  depth,		
		-width, -height, -depth,
		 width, -height, -depth,
		 width, -height,  depth,
		 width, -height,  depth,
		-width, -height,  depth,
		-width, -height, -depth,
		-width,  height, -depth,
		 width,  height, -depth,
		 width,  height,  depth,
		 width,  height,  depth,
		-width,  height,  depth,
		-width,  height, -depth
	};

	GLfloat uvdata[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f
	};

	GLfloat colors[] =
	{
		0,0,0,0
	};

	GLushort indicies[] =
	{
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35
	};

	m_VertexArray = new VertexArray();

	m_VertexArray->addBuffer(new Buffer(verticies, sizeof(verticies), 3), 0);
	m_VertexArray->addBuffer(new Buffer(uvdata, sizeof(uvdata), 2), 1);
	m_VertexArray->addBuffer(new Buffer(colors, 4, 4), 2);

	m_IndexBuffer = new IndexBuffer(indicies, sizeof(indicies));
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
