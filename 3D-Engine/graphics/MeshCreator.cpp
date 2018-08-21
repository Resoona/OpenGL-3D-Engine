#include "MeshCreator.h"

Mesh* CreateCube(float size, MaterialInstance* material)
{
	using namespace glm;

	Vertex data[8];

	memset(data, 0, 8 * sizeof(Vertex));

	data[0].position = vec3(-size / 2.0f, -size / 2.0f, size / 2.0f);
	data[1].position = vec3(size / 2.0f, -size / 2.0f, size / 2.0f);
	data[2].position = vec3(size / 2.0f, size / 2.0f, size / 2.0f);
	data[3].position = vec3(-size / 2.0f, size / 2.0f, size / 2.0f);
	data[4].position = vec3(-size / 2.0f, -size / 2.0f, -size / 2.0f);
	data[5].position = vec3(size / 2.0f, -size / 2.0f, -size / 2.0f);
	data[6].position = vec3(size / 2.0f, size / 2.0f, -size / 2.0f);
	data[7].position = vec3(-size / 2.0f, size / 2.0f, -size / 2.0f);

	data[0].normal = vec3(-1.0f, -1.0f, 1.0f);
	data[1].normal = vec3(1.0f, -1.0f, 1.0f);
	data[2].normal = vec3(1.0f, 1.0f, 1.0f);
	data[3].normal = vec3(-1.0f, 1.0f, 1.0f);
	data[4].normal = vec3(-1.0f, -1.0f, -1.0f);
	data[5].normal = vec3(1.0f, -1.0f, -1.0f);
	data[6].normal = vec3(1.0f, 1.0f, -1.0f);
	data[7].normal = vec3(-1.0f, 1.0f, -1.0f);

	Buffer* buffer = new Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
	buffer->bind();
	buffer->SetData(8 * sizeof(Vertex), data);

	buffer->layout.Push<vec3>("position");
	buffer->layout.Push<vec3>("normal");
	buffer->layout.Push<vec2>("uv");

	VertexArray* va = new VertexArray();
	va->bind();
	va->PushBuffer(buffer);


	//m_VertexArray->addBuffer(new Buffer(verticies, sizeof(verticies), 3), 0);
	
	uint* indices = new uint[36]
	{
		0, 1, 2, 2, 3, 0,
		3, 2, 6, 6, 7, 3,
		7, 6, 5, 5, 4, 7,
		4, 0, 3, 3, 7, 4,
		0, 1, 5, 5, 4, 0,
		1, 5, 6, 6, 2, 1
	};

	IndexBuffer* ib = new IndexBuffer(indices, 36);
	return new Mesh(va, ib, material);

	
}
