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
		std::vector<RendererUniform> uniforms;
	};