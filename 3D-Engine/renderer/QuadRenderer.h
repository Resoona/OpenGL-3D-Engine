#pragma once
#include "../graphics/camera.h"
#include "../glm/glm/glm.hpp"
#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../graphics/model.h"

#include <vector>

class QuadRenderer
{

private:
	std::vector<glm::vec3> m_Quads;

	Model m_quadModel;
	Shader m_shader;
	
	//Store Texture too



public:
	QuadRenderer();

	~QuadRenderer();

	void add(const glm::vec3& position);

	void renderQuads(const Camera& camera);


};
