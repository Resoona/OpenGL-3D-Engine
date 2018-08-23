#include "Scene.h"
#include "../renderer/Renderer3D.h"
#include <iostream>


Scene::Scene()
{
	m_Camera = new Camera();
}

Scene::Scene(Camera* camera)
	:m_Camera(camera)
{
	
}

Scene::~Scene()
{
	for (uint i = 0; i < m_Entities.size(); i++)
		delete m_Entities[i];

	m_Entities.clear();
}

void Scene::Add(entity::Entity* entity)
{
	m_Entities.push_back(entity);
	if (!entity->GetComponent<entity::component::TransformComponent>())
	{
		std::cout << "Entity does not have Transform, creating..." << std::endl;
		entity->AddComponent(new entity::component::TransformComponent(glm::mat4(1.0)));
	}
}

void Scene::Render(Renderer3D& renderer)
{
	Camera* camera = m_Camera;
	camera->Update();

	renderer.Begin();

	for (entity::Entity* entity : m_Entities)
	{
		entity::component::MeshComponent* mesh = entity->GetComponent<entity::component::MeshComponent>();
		if (mesh)
		{
			entity::component::TransformComponent* tc = entity->GetComponent<entity::component::TransformComponent>();
			if (!tc) std::cout << "Mesh does not have transform!" << std::endl; // Meshes MUST have transforms
			assert(tc);
			
			renderer.SubmitMesh(camera, mesh->mesh, tc->transform);
		}
	}

	renderer.End();
}
