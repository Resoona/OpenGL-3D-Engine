#pragma once
#include "Renderer3D.h"
#include "../graphics/window.h"



class ForwardRenderer : public Renderer3D
{
private:
	byte * m_VSSystemUniformBuffer;
	uint m_VSSystemUniformBufferSize;
	byte* m_PSSystemUniformBuffer;
	uint m_PSSystemUniformBufferSize;

	std::vector<uint> m_VSSystemUniformBufferOffsets;
	std::vector<uint> m_PSSystemUniformBufferOffsets;

	void SetSystemUniforms(Shader* shader);
public:
	ForwardRenderer();
	void Init() override;
	void Begin() override;
	void BeginScene(Camera* camera) override;
	void Submit(const RenderCommand& command) override;
	void SubmitMesh(Camera* camera, Mesh* mesh, const glm::mat4& transform) override;
	void End() override;
	void EndScene() override;
	void Present() override;
};

