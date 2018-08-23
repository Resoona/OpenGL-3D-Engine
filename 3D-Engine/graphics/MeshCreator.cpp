#include "MeshCreator.h"

struct VertexData
{
	glm::vec3 vertex;
	glm::vec2 uv;
	glm::vec2 mask_uv;
	float tid;
	float mid;
	unsigned int color;
};

VertexArray* CreateQuad(float x, float y, float width, float height)
{
	using namespace glm;

	VertexData data[4];

	data[0].vertex = vec3(x, y, 0);
	data[0].uv = vec2(0, 1);

	data[1].vertex = vec3(x, y + height, 0);
	data[1].uv = vec2(0, 0);

	data[2].vertex = vec3(x + width, y + height, 0);
	data[2].uv = vec2(1, 0);

	data[3].vertex = vec3(x + width, y, 0);
	data[3].uv = vec2(1, 1);

	Buffer* buffer = new Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
	buffer->Bind();
	buffer->SetData(sizeof(VertexData) * 4, data);

	buffer->layout.Push<vec3>("position");
	buffer->layout.Push<vec2>("uv");
	buffer->layout.Push<vec2>("mask_uv");
	buffer->layout.Push<float>("tid");
	buffer->layout.Push<float>("mid");
	buffer->layout.Push<GLbyte>("color", 4, true);

	VertexArray* result = new VertexArray();
	result->Bind();
	result->PushBuffer(buffer);

	return result;
}

VertexArray* CreateQuad(const glm::vec2& position, const glm::vec2& size)
{
	return CreateQuad(position.x, position.y, size.x, size.y);
}


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
	buffer->Bind();
	buffer->SetData(8 * sizeof(Vertex), data);

	buffer->layout.Push<vec3>("position");
	buffer->layout.Push<vec3>("normal");
	buffer->layout.Push<vec2>("uv");

	VertexArray* va = new VertexArray();
	va->Bind();
	va->PushBuffer(buffer);

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
