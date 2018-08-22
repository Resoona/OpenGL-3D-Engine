#pragma once
#include "buffers/VertexArray.h"
#include "buffers/IndexBuffer.h"
#include "Material.h"
#include "../renderer/IRenderable.h"

class Renderer3D;


struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};

class Mesh : public IRenderable
{
private:
	VertexArray * m_VertexArray;
	IndexBuffer* m_IndexBuffer;
	MaterialInstance* m_MaterialInstance;
public:
	Mesh(VertexArray* vertexArray, IndexBuffer* indexBuffer, MaterialInstance* materialInstance);

	~Mesh();

	inline void SetMaterial(MaterialInstance* materialInstance) { m_MaterialInstance = materialInstance; }
	inline MaterialInstance* GetMaterialInstance() const { return m_MaterialInstance; }

	void Render(Renderer3D& renderer) override;
};
