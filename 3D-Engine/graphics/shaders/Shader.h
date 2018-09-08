#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "../../utils/StringUtils.h"
#include "../../utils/FileUtils.h"
#include "ShaderUniform.h"
#include "ShaderResource.h"

#define SHADER_VERTEX_INDEX		0
#define SHADER_UV_INDEX			1
#define SHADER_MASK_UV_INDEX	2
#define SHADER_TID_INDEX		3
#define SHADER_MID_INDEX		4
#define SHADER_COLOR_INDEX		5

#define SHADER_UNIFORM_PROJECTION_MATRIX_NAME	"pr_matrix"
#define SHADER_UNIFORM_VIEW_MATRIX_NAME			"vw_matrix"
#define SHADER_UNIFORM_MODEL_MATRIX_NAME		"ml_matrix"

class Shader
{
	
private:
	enum class ShaderType
	{
		UNKNOWN, VERTEX, FRAGMENT
	};
	String m_Name, m_Path;
	String m_Source;
	String m_VertexSource, m_FragmentSource;
	uint m_ShaderID;

	ShaderUniformBufferList m_VSUniformBuffers;
	ShaderUniformBufferList m_PSUniformBuffers;
	GLShaderUniformBufferDeclaration* m_VSUserUniformBuffer;
	GLShaderUniformBufferDeclaration* m_PSUserUniformBuffer;
	ShaderResourceList m_Resources;
	ShaderStructList m_Structs;

	std::vector<ShaderUniformDeclaration*> m_Uniforms;
public:
	Shader(const String& name, const String& source);
	~Shader();
	void Bind() const;
	void Unbind() const;

	void SetUniform(const String& name, byte* data);
	void ResolveAndSetUniform(ShaderUniformDeclaration* uniform, byte* data, int offset);
	void ResolveAndSetUniform(uint index, byte* data);
	void ResolveAndSetUniforms(byte* data, uint size);

	inline GLint getShaderID() const { return m_ShaderID; };
	inline const ShaderResourceList& GetResources() const { return m_Resources; }
	inline const std::vector<ShaderUniformDeclaration*>& GetUniformDeclarations() const { return m_Uniforms; }

	bool HasUniform(const String& name) const;
	ShaderUniformDeclaration* GetUniformDeclaration(uint location);


private:
	uint Load(const String& vertSrc, const String& fragSrc);

	
	void PreProcess(const String& source, String** shaders);
	void Parse(const String& vertexSource, const String& fragmentSource);
	void ParseUniforms(const std::vector<String>& lines);
	
	void ResolveUniforms();
	void ValidateUniforms();
	bool IsSystemUniform(ShaderUniformDeclaration* uniform) const;

	GLint GetUniformLocation(const String& name);

	ShaderUniformDeclaration::Type GetUniformTypeFromString(const String& token);
	ShaderUniformDeclaration* FindUniformDeclaration(const String& name);

	void SetUniform1f(const String& name, float value);
	void SetUniform1fv(const String& name, float* value, int count);
	void SetUniform1i(const String& name, int value);
	void SetUniform1iv(const String& name, int* value, int count);
	void SetUniform2f(const String& name, const glm::vec2& vector);
	void SetUniform3f(const String& name, const glm::vec3& vector);
	void SetUniform4f(const String& name, const glm::vec4& vector);
	void SetUniformMat4(const String& name, const glm::mat4& matrix);


	void SetUniform1f(uint location, float value);
	void SetUniform1fv(uint location, float* value, int count);
	void SetUniform1i(uint location, int value);
	void SetUniform1iv(uint location, int* value, int count);
	void SetUniform2f(uint location, const glm::vec2& vector);
	void SetUniform3f(uint location, const glm::vec3& vector);
	void SetUniform4f(uint location, const glm::vec4& vector);
	void SetUniformMat4(uint location, const glm::mat4& matrix);

public:
	static Shader* FromFile(const String& name, const String& filepath);
	static Shader* FromSource(const String& name, const String& source);
};
