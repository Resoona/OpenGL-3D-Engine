#include "Material.h"
#include <iostream>


Material::Material(Shader* shader)
	:m_Shader(shader)
{
	InitUniformStorage();
	m_Resources = &m_Shader->GetResources();
}

Material::~Material()
{
	delete m_Shader;
}

void Material::InitUniformStorage()
{
	m_UniformDataSize = 0;
	const std::vector<ShaderUniformDeclaration*>& uniforms = m_Shader->GetUniformDeclarations();
	for (ShaderUniformDeclaration* uniform : uniforms)
		m_UniformDataSize += uniform->GetSize();

	m_UniformData = new GLbyte[m_UniformDataSize];
	memset(m_UniformData, 0, m_UniformDataSize);
}

const ShaderUniformDeclaration* Material::GetUniformDeclaration(const String& name) const
{
	for (ShaderUniformDeclaration* uniform : m_Shader->GetUniformDeclarations())
	{
		if (uniform->GetName() == name)
			return uniform;
	}
	return nullptr;
}

ShaderResourceDeclaration* Material::FindResourceDeclaration(const String& name)
{
	for (ShaderResourceDeclaration* resource : *m_Resources)
	{
		if (resource->GetName() == name)
			return resource;
	}
	return nullptr;
}

void Material::DumpUniformData() const
{
	std::cout << "Dumping uniforms for Material " << (long)this << std::endl;
	const std::vector<ShaderUniformDeclaration*>& uniforms = m_Shader->GetUniformDeclarations();
	for (GLuint i = 0; i < uniforms.size(); i++)
	{
		ShaderUniformDeclaration* declaration = uniforms[i];
		switch (declaration->GetType())
		{
		case ShaderUniformDeclaration::Type::MAT4:
			//SPARKY_INFO(declaration->GetName(), " = ", GetUniform<glm::mat4>(declaration)->ToString());
			break;
		}
	}
}

void Material::SetTexture(const String& name, Texture* texture)
{
	ShaderResourceDeclaration* declaration = FindResourceDeclaration(name);
	assert(declaration);
	uint slot = declaration->GetRegister();
	if (m_Textures.size() <= slot)
		m_Textures.resize(slot + 1);
	m_Textures[slot] = texture;
}

void Material::Bind() const
{
	m_Shader->Bind();
	
}

void Material::UnBind() const
{
	m_Shader->Unbind();
}

MaterialInstance::MaterialInstance(Material* material)
	: m_Material(material), m_SetUniforms(0)
{
	InitUniformStorage();

	m_Resources = &m_Material->GetShader()->GetResources();
}

void MaterialInstance::InitUniformStorage()
{
	m_UniformDataSize = 0;
	const std::vector<ShaderUniformDeclaration*>& uniforms = m_Material->m_Shader->GetUniformDeclarations();
	for (ShaderUniformDeclaration* uniform : uniforms)
		m_UniformDataSize += uniform->GetSize();

	m_UniformData = new byte[m_UniformDataSize];
	memset(m_UniformData, 0, m_UniformDataSize);
}

int MaterialInstance::GetUniformDeclarationIndex(const String& name) const
{
	std::vector<ShaderUniformDeclaration*> uniforms = m_Material->m_Shader->GetUniformDeclarations();
	for (uint i = 0; i < uniforms.size(); i++)
	{
		if (uniforms[i]->GetName() == name)
			return i;
	}
	return -1;
}

ShaderResourceDeclaration* MaterialInstance::FindResourceDeclaration(const String& name)
{
	for (ShaderResourceDeclaration* resource : *m_Resources)
	{
		if (resource->GetName() == name)
			return resource;
	}
	return nullptr;
}

void MaterialInstance::UnsetUniform(const String& name)
{
	int index = GetUniformDeclarationIndex(name);
	uint mask = !(1 << index);
	m_SetUniforms &= mask;
}

void MaterialInstance::SetTexture(const String& name, Texture* texture)
{
	ShaderResourceDeclaration* declaration = FindResourceDeclaration(name);
	uint slot = declaration->GetRegister();
	if (m_Textures.size() <= slot)
	{
		m_Textures.resize(slot + 1);
	}
	m_Textures[slot] = texture;
}

void MaterialInstance::Bind() const
{
	// TODO: Textures. This needs to be resolved by the renderer.

	m_Material->Bind();

	uint overrides = m_SetUniforms;
	uint index = 0;
	while (overrides > 0)
	{
		if (overrides & 1)
			m_Material->m_Shader->ResolveAndSetUniform(index, m_UniformData);

		overrides >>= 1;
		index++;
	}
}

void MaterialInstance::Unbind() const
{
	m_Material->m_Shader->Unbind();
}

