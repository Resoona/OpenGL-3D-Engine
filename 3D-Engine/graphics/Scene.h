#pragma once

#include "Camera.h"
#include "../entity/Entity.h"

class Renderer3D;



class Scene
{
private:
	std::vector<entity::Entity*> m_Entities;
	Camera* m_Camera;
public:
	Scene();
	Scene(Camera* camera);
	~Scene();
	void Add(entity::Entity* entity);
	void Update();
	void Render(Renderer3D& renderer);

	inline Camera* GetCamera() { return m_Camera; }

	const std::vector<entity::Entity*>& GetEntities() const { return m_Entities; }
};