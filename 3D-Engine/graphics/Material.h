#pragma once
#include "Shader.h"


class Material
{

private:
	Shader * m_Shader;
	GLchar m_UniformName;
	glm::mat4 m_UniformData;

public:
	Material(Shader* shader);
	~Material();

	void Bind() const;
	void UnBind() const;

	inline void SetUniform(const GLchar& name, const glm::mat4& value)
	{
		m_UniformName = name;
		m_UniformData = value;
	}
		
};

class MaterialInstance
{
private:
	Material * m_Material;
public:
	MaterialInstance(Material* material);
	inline Material* GetMaterial() const { return m_Material; }

};
