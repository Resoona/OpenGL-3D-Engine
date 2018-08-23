#pragma once
#include "Renderer3D.h"



class ForwardRenderer : public Renderer3D
{
private:
	void SetRequiredUniforms(Shader* shader, const std::vector<RendererUniform>& uniforms);
public:
	ForwardRenderer();
	void Init() override;
	void Begin() override;
	void Submit(const RenderCommand& command) override;
	void SubmitMesh(Camera* camera, Mesh* mesh, const glm::mat4& transform) override;
	void End() override;
	void Present() override;
};

