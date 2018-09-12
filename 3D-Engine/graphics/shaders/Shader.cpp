#include "Shader.h"
#include "../../utils/FileUtils.h"
#include "GLShader.h"


Shader* Shader::CreateFromFile(const String& name, const String& filepath, void* address)
{

	String source = utils::ReadFile(filepath);

	GLShader* result = address ? new(address) GLShader(name, source) : new GLShader(name, source);
	result->m_Path = filepath;
	return result;

	}
