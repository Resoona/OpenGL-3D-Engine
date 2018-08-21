#pragma once
#include "Mesh.h"

class Renderer3D;


class Scene
{
private:
	std::vector<Mesh*> m_Meshes; 
public:
	Scene();
	~Scene();
	void Add(Mesh* mesh);
	void Render(Renderer3D& renderer);

	const std::vector<Mesh*>& GetMeshes() const { return m_Meshes; }
};