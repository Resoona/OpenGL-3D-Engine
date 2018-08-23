#pragma once
#include <iostream>

#include "../graphics/Texture.h"
#include "../graphics/StaticSprite.h"
#include "../src/InputHandler.h"
#include "../renderer/Renderer.h"
#include "../graphics/MeshCreator.h"
#include "../graphics/Scene.h"
#include "../renderer/ForwardRenderer.h"
#include "../graphics/Model.h"


	MaterialInstance* m_CubeMaterial;
	MaterialInstance* m_PlantMaterial;
	entity::Entity* m_Cube;
	entity::Entity* m_HousePlant;
	entity::Entity* m_Quad;
	MaterialInstance* m_DefaultMaterial;
	Renderer3D* m_Renderer;
	
	
	
