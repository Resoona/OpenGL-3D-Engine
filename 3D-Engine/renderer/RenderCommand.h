#pragma once
#include "../graphics/Mesh.h"

	struct RendererUniform
	{
		String uniform;
		byte* value;
	};

	struct RenderCommand
	{
		Mesh* mesh;
		glm::mat4 transform;
		Shader* shader;
		std::vector<RendererUniform> uniforms;
	};