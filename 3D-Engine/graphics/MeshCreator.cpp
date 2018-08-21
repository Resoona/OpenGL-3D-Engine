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

	
}
