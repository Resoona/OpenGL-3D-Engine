#pragma once
#include "RenderCommand.h"
#include "../graphics/Camera.h"

//
// Base class for all 3D renderers.


class Renderer3D
{
protected:
	std::vector<RenderCommand> m_CommandQueue;
public:
	virtual void Init() = 0;
	virtual void Begin() = 0;
	virtual void Submit(const RenderCommand& command) = 0;
	virtual void SubmitMesh(Camera* camera, Mesh* mesh, const glm::mat4& transform) = 0;
	virtual void End() = 0;
	virtual void Present() = 0;

};
