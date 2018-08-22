#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "glm/glm.hpp"

#include <unordered_map>

#include "Mesh.h"
class Model : public IRenderable
{
private:
	Mesh * m_Mesh;
public:
	// This eventually needs to be replaced by a global Asset Server.
	Model(const String& path, MaterialInstance* materialInstance);
	~Model();

	void Render(Renderer3D& renderer) override;

	inline Mesh* GetMesh() const { return m_Mesh; }
private:
	struct VertexSet
	{
		std::vector<glm::vec3> positions, normals;
		std::vector<glm::vec2> uvs;
	};
	// TODO: Replace with uvec3, whenever that begins to exist
public:
	struct IndexSet
	{
		uint position;
		uint uv;
		uint normal;

		bool operator==(const IndexSet& other) const
		{
			return position == other.position && uv == other.uv && normal == other.uv;
		}
	};

	friend struct std::hash<Model::IndexSet>;

	void Load(const String& path);
	void InsertVertex(std::vector<Vertex>& vertices, std::vector<uint>& indices, std::unordered_map<IndexSet, int>& mapping, VertexSet& inputVertices, IndexSet& indexSet);
};
