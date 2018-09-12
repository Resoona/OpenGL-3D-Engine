#include "ForwardRenderer.h"
#include "Renderer.h"
#include "../graphics/Light.h"

enum VSSystemUniformIndices : int32
{
	VSSystemUniformIndex_ProjectionMatrix = 0,
	VSSystemUniformIndex_ViewMatrix = 1,
	VSSystemUniformIndex_ModelMatrix = 2,
	VSSystemUniformIndex_CameraPosition = 3,
	VSSystemUniformIndex_Size
};

enum PSSystemUniformIndices : int32
{
	PSSystemUniformIndex_Lights = 0,
	PSSystemUniformIndex_Size
};

using namespace glm;

ForwardRenderer::ForwardRenderer()
{
	//TODO get Window Params
	SetScreenBufferSize(960, 540);
	Init();
}

void ForwardRenderer::Init()
{
	m_CommandQueue.reserve(1000);

	//
	// Vertex shader system uniforms
	//
	m_VSSystemUniformBufferSize = sizeof(mat4) + sizeof(mat4) + sizeof(vec3) + sizeof(mat4);
	m_VSSystemUniformBuffer = new byte[m_VSSystemUniformBufferSize];
	memset(m_VSSystemUniformBuffer, 0, m_VSSystemUniformBufferSize);
	m_VSSystemUniformBufferOffsets.resize(VSSystemUniformIndex_Size);

	// Per Scene System Uniforms
	m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ProjectionMatrix] = 0;
	m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ViewMatrix] = m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ProjectionMatrix] + sizeof(mat4);
	m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ModelMatrix] = m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ViewMatrix] + sizeof(mat4);

	// Per Mesh System Uniforms
	// Note: Model Matrix should be here instead of camera position; this will get sorted when it gets moved to a separate buffer
	m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_CameraPosition] = m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ModelMatrix] + sizeof(mat4);

	//
	// Pixel/fragment shader system uniforms
	//
	m_PSSystemUniformBufferSize = sizeof(Light);
	m_PSSystemUniformBuffer = new byte[m_PSSystemUniformBufferSize];
	memset(m_PSSystemUniformBuffer, 0, m_PSSystemUniformBufferSize);
	m_PSSystemUniformBufferOffsets.resize(PSSystemUniformIndex_Size);

	// Per Scene System Uniforms
	m_PSSystemUniformBufferOffsets[PSSystemUniformIndex_Lights] = 0;

}

void ForwardRenderer::Begin()
{
	//Renderer::SetViewport(0, 0, m_ScreenBufferWidth, m_ScreenBufferHeight);

	m_CommandQueue.clear();
	m_SystemUniforms.clear();
}

void ForwardRenderer::BeginScene(Camera* camera)
{
	memcpy(m_VSSystemUniformBuffer + m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ProjectionMatrix], &camera->GetProjectionMatrix(), sizeof(mat4));
	memcpy(m_VSSystemUniformBuffer + m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ViewMatrix], &camera->GetViewMatrix(), sizeof(mat4));
	memcpy(m_VSSystemUniformBuffer + m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_CameraPosition], &camera->GetPosition(), sizeof(vec3));

}

void ForwardRenderer::Submit(const RenderCommand& command)
{
	m_CommandQueue.push_back(command);
}


void ForwardRenderer::SubmitMesh(Camera* camera, Mesh* mesh, const glm::mat4& transform)
{
	RenderCommand command;
	command.mesh = mesh;
	command.transform = transform; // TODO: Come up with a better solution to per-mesh system uniforms
	command.shader = mesh->GetMaterialInstance()->GetMaterial()->GetShader();
	Submit(command);
}

void ForwardRenderer::End()
{

}

void ForwardRenderer::EndScene()
{
}

void ForwardRenderer::SetSystemUniforms(Shader* shader)
{
	// TODO: Set per-mesh buffer to slot 1
	shader->SetVSSystemUniformBuffer(m_VSSystemUniformBuffer, m_VSSystemUniformBufferSize, 0);
	shader->SetPSSystemUniformBuffer(m_PSSystemUniformBuffer, m_PSSystemUniformBufferSize, 0);
}

void ForwardRenderer::Present()
{
	// TODO: Shader binding, texture sorting, visibility testing, etc.
	for (uint i = 0; i < m_CommandQueue.size(); i++)
	{
		RenderCommand& command = m_CommandQueue[i];
		//MaterialInstance* material = command.mesh->GetMaterialInstance();
		//int materialRenderFlags = material->GetRenderFlags();
		//Renderer::SetDepthTesting((materialRenderFlags & (int)Material::RenderFlags::DISABLE_DEPTH_TEST) == 0);
		memcpy(m_VSSystemUniformBuffer + m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ModelMatrix], &command.transform, sizeof(mat4));
		SetSystemUniforms(command.shader);
		command.mesh->Render(*this);
		//std::cout << "rendered" << std::endl;

	}
}
