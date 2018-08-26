#pragma once
#include "shaders/Shader.h"
#include "../utils/StringUtils.h"
#include "Texture.h"
#include "shaders/ShaderResource.h"


class Material
{

private:
	friend class MaterialInstance;

	Shader * m_Shader;
	GLbyte* m_UniformData;
	GLuint m_UniformDataSize;

protected:
	std::vector<Texture*> m_Textures;
	const ShaderResourceList* m_Resources;

public:
	Material(Shader* shader);
	~Material();

	void Bind() const;
	void UnBind() const;
	void DumpUniformData() const;
	void SetTexture(const String& name, Texture* texture);

	inline Shader* GetShader() const { return m_Shader; }

	template<typename T>
	inline void SetUniform(const String& name, const T& value)
	{
		//m_UniformData = value;
		m_Shader->SetUniformMat4(name, value);
		
	}

	template<typename T>
	inline const T* GetUniform(const String& name) const
	{
		return GetUniform<T>(GetUniformDeclaration(name));
	}

	template<typename T>
	const T* GetUniform(const ShaderUniformDeclaration* uniform) const
	{
		return (T*)&m_UniformData[uniform->GetOffset()];
	}

protected:
	void InitUniformStorage();
	const ShaderUniformDeclaration* GetUniformDeclaration(const String& name) const;
	ShaderResourceDeclaration* FindResourceDeclaration(const String& name);
};

class MaterialInstance
{
private:
	Material * m_Material;
	byte* m_UniformData;
	uint m_UniformDataSize;
	uint m_SetUniforms;


	std::vector<Texture*> m_Textures;

	const ShaderResourceList* m_Resources;
public:
	MaterialInstance(Material* material);

	inline Material* GetMaterial() const { return m_Material; }

	void Bind() const;
	void Unbind() const;
	void UnsetUniform(const String& name);
	void SetTexture(const String& name, Texture* texture);

	template<typename T>
	void SetUniform(const String& name, const T& value)
	{
		int index = GetUniformDeclarationIndex(name);
		if (index == -1)
		{
			std::cout << "Could not find uniform " << name << std::endl;
			return;
		}
		ShaderUniformDeclaration* uniform = m_Material->m_Shader->GetUniformDeclarations()[index];
		memcpy(m_UniformData + uniform->GetOffset(), &value, uniform->GetSize());

		m_SetUniforms |= 1 << index;
	}
private:
	void InitUniformStorage();
	int GetUniformDeclarationIndex(const String& name) const;
	ShaderResourceDeclaration* FindResourceDeclaration(const String& name);
};