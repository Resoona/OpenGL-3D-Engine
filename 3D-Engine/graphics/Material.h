#pragma once
#include "Shader.h"


class Material
{

private:
	Shader * m_Shader;
	std::string m_UniformName;
	glm::mat4 m_UniformData;

public:
	Material(Shader* shader);
	~Material();

	void Bind() const;
	void UnBind() const;

	inline void SetUniform(const std::string& name, const glm::mat4& value)
	{
		m_UniformName = name;
		m_UniformData = value;
		m_Shader->setUniformMat4(name, value);
		
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
