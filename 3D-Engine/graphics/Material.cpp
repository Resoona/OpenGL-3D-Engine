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

MaterialInstance::MaterialInstance(Material* material)
	: m_Material(material)
{
}

