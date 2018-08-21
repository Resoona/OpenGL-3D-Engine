#include "Material.h"


Material::Material(Shader* shader)
	:m_Shader(shader)
{
	
}

Material::~Material()
{
	delete m_Shader;
}

void Material::Bind() const
{
	m_Shader->enable();
	
}

void Material::UnBind() const
{
	m_Shader->disable();
}

MaterialInstance::MaterialInstance(Material* material)
	: m_Material(material)
{
}

