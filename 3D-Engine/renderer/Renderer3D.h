#pragma once
#include "RenderCommand.h"
#include "../graphics/Camera.h"

//
// Base class for all 3D renderers.
typedef std::vector<RenderCommand> CommandQueue;
typedef std::vector<RendererUniform> SystemUniformList;

class Renderer3D
{
protected:
	uint m_ScreenBufferWidth, m_ScreenBufferHeight;
	CommandQueue m_CommandQueue;
	SystemUniformList m_SystemUniforms;
public:
	virtual void Init() = 0;
	virtual void Begin() = 0;
	virtual void BeginScene(Camera* camera) = 0;
	virtual void Submit(const RenderCommand& command) = 0;
	virtual void SubmitMesh(Camera* camera, Mesh* mesh, const glm::mat4& transform) = 0;
	virtual void End() = 0;
	virtual void EndScene() = 0;
	virtual void Present() = 0;

	virtual void SetScreenBufferSize(uint width, uint height) { m_ScreenBufferWidth = width; m_ScreenBufferHeight = height; }

};
