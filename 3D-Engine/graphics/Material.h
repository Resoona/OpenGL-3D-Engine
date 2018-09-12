#pragma once
#include "shaders/Shader.h"
#include "../utils/StringUtils.h"
#include "Texture.h"
#include "shaders/ShaderResource.h"


class Material
{

private:
	friend class MaterialInstance;
protected:

	Shader* m_Shader;

	byte* m_VSUserUniformBuffer;
	uint m_VSUserUniformBufferSize;

	byte* m_PSUserUniformBuffer;
	uint m_PSUserUniformBufferSize;

	std::vector<Texture*> m_Textures;

	const ShaderUniformList* m_VSUserUniforms;
	const ShaderUniformList* m_PSUserUniforms;
	const ShaderResourceList* m_Resources;


public:
	Material(Shader* shader);
	~Material();

	void Bind();
	void Unbind();
	void SetUniformData(const String& uniform, byte* data);
	void DumpUniformData() const;
	void SetTexture(const String& name, Texture* texture);

	inline Shader* GetShader() const { return m_Shader; }

	template<typename T>
	inline void SetUniform(const String& name, const T& data)
	{
		byte* buffer;
		ShaderUniformDeclaration* declaration = FindUniformDeclaration(name, &buffer);
		if (!declaration)
		{
			std::count << "Could not find uniform with name '" << name << "'!" << std::endl;
			return;
		}
		memcpy(buffer + declaration->GetOffset(), &data, declaration->GetSize());
		
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
	void AllocateStorage();
	ShaderUniformDeclaration* FindUniformDeclaration(const String& name, byte** outBuffer = nullptr);
	ShaderResourceDeclaration* FindResourceDeclaration(const String& name);
};

class MaterialInstance
{
private:
	Material * m_Material;
	byte* m_VSUserUniformBuffer;
	uint m_VSUserUniformBufferSize;

	byte* m_PSUserUniformBuffer;
	uint m_PSUserUniformBufferSize;

	std::vector<Texture*> m_Textures;

	const ShaderUniformList* m_VSUserUniforms;
	const ShaderUniformList* m_PSUserUniforms;
	const ShaderResourceList* m_Resources;


public:
	MaterialInstance(Material* material);

	inline Material* GetMaterial() const { return m_Material; }

	void Bind();
	void Unbind();
	void SetUniformData(const String& uniform, byte* data);
	void SetTexture(const String& name, Texture* texture);

	template<typename T>
	void SetUniform(const String& name, const T& data)
	{
		byte* buffer;
		ShaderUniformDeclaration* declaration = FindUniformDeclaration(name, &buffer);
		assert(declaration);
		memcpy(buffer + declaration->GetOffset(), &data, declaration->GetSize());

	}

	template<typename T>
	const T* GetUniform(const String& name) const
	{
		return GetUniform<T>(GetUniformDeclaration(name));
	}
private:
	void AllocateStorage();
	int GetUniformDeclarationIndex(const String& name) const;
	ShaderUniformDeclaration* FindUniformDeclaration(const String& name, byte** outBuffer = nullptr);
	ShaderResourceDeclaration* FindResourceDeclaration(const String& name);
};