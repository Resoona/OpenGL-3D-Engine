#include "GLShader.h"
#include "../../utils/String.h"


bool GLShader::TryCompile(const String& source, String& error)
	{
		String vert, frag;
		String* shaders[2] = { &vert, &frag };
		PreProcess(source, shaders);
		ShaderErrorInfo info;
		if (!GLShader::Compile(shaders, info))
		{
			error = info.message[info.shader];
			return false;
		}
		return true;
	}

	bool GLShader::TryCompileFromFile(const String& filepath, String& error)
	{
		String source = utils::ReadFile(filepath);
		return TryCompile(source, error);
	}


	GLShader::GLShader(const String& name, const String& source)
		: m_Name(name), m_Source(source)
	{
		Init();
	}

	GLShader::~GLShader()
	{
	}

	void GLShader::Init()
	{
		m_VSUserUniformBuffer = nullptr;
		m_PSUserUniformBuffer = nullptr;

		String* shaders[2] = { &m_VertexSource, &m_FragmentSource };
		PreProcess(m_Source, shaders);
		Parse(m_VertexSource, m_FragmentSource);
		ShaderErrorInfo error;
		m_ShaderID = Compile(shaders, error);
		if (!m_ShaderID)
			std::cout << (error.message[error.shader]) << std::endl;
		assert(m_ShaderID);
		ResolveUniforms();
		ValidateUniforms();
	}

	void GLShader::Shutdown()
	{
		glDeleteProgram(m_ShaderID);
	}


	void GLShader::PreProcess(const String& source, String** shaders)
	{
		ShaderType type = ShaderType::UNKNOWN;

		std::vector<String> lines = GetLines(source);
		for (uint i = 0; i < lines.size(); i++)
		{
			const char* str = lines[i].c_str();
			if (strstr(str, "#shader"))
			{
				if (strstr(str, "vertex"))
					type = ShaderType::VERTEX;
				else if (strstr(str, "fragment"))
					type = ShaderType::FRAGMENT;
			}
			else if (type != ShaderType::UNKNOWN)
			{
				shaders[(int32)type - 1]->append(str);
				shaders[(int32)type - 1]->append("\n");
			}
		}
	}


	uint GLShader::Compile(String** shaders, ShaderErrorInfo& info)
	{
		const char* vertexSource = shaders[0]->c_str();
		const char* fragmentSource = shaders[1]->c_str();

		uint program = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);

		GLint result;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertex, length, &length, &error[0]);
			String errorMessage(&error[0]);
			info.shader = 0;
			info.message[info.shader] += "Failed to compile vertex shader!\n";
			info.message[info.shader] += errorMessage;
			glDeleteShader(vertex);
			return 0;
		}

		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragment, length, &length, &error[0]);
			String errorMessage(&error[0], length);
			int32 lineNumber;
			sscanf(&error[0], "%*s %*d:%d", &lineNumber);
			info.shader = 1;
			info.message[info.shader] += "Failed to compile fragment shader!\n";

			// String line = utils::GetLines(m_FragmentSource)[lineNumber - 1];
			// uint absoluteLine = utils::GetLines(m_VertexSource).size() + lineNumber + 2;
			// info.message += lineNumber + "(" + StringFormat::ToString(absoluteLine) + ")  " + line;
			info.line[info.shader] = lineNumber;
			info.message[info.shader] += errorMessage;
			glDeleteShader(fragment);
			return 0;
		}

		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);
		glValidateProgram(program);

		glDetachShader(program, vertex);
		glDetachShader(program, fragment);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
	}

	void GLShader::Bind() const
	{
		glUseProgram(m_ShaderID);
		//s_CurrentlyBound = this;
	}

	void GLShader::Unbind() const
	{
		glUseProgram(0);
		//s_CurrentlyBound = nullptr;
	}

	void GLShader::Parse(const String& vertexSource, const String& fragmentSource)
	{
		m_VSUniformBuffers.push_back(new GLShaderUniformBufferDeclaration("Global", 0));
		m_PSUniformBuffers.push_back(new GLShaderUniformBufferDeclaration("Global", 1));

		const char* token;
		const char* vstr;
		const char* fstr;

		// Vertex Shader
		vstr = vertexSource.c_str();
		while (token = FindToken(vstr, "struct"))
			ParseUniformStruct(GetBlock(token, &vstr), 0);

		vstr = vertexSource.c_str();
		while (token = FindToken(vstr, "uniform"))
			ParseUniform(GetStatement(token, &vstr), 0);

		// Fragment Shader
		fstr = fragmentSource.c_str();
		while (token = FindToken(fstr, "struct"))
			ParseUniformStruct(GetBlock(token, &fstr), 1);

		fstr = fragmentSource.c_str();
		while (token = FindToken(fstr, "uniform"))
			ParseUniform(GetStatement(token, &fstr), 1);
	}

	void GLShader::ParseUniform(const String& statement, uint shaderType)
	{
		std::vector<String> tokens = Tokenize(statement);
		uint index = 0;

		index++; // "uniform"
		String typeString = tokens[index++];
		String name = tokens[index++];
		// Strip ; from name if present
		if (const char* s = strstr(name.c_str(), ";"))
			name = String(name.c_str(), s - name.c_str());

		String n(name);
		int32 count = 1;
		const char* namestr = n.c_str();
		if (const char* s = strstr(namestr, "["))
		{
			name = String(namestr, s - namestr);

			const char* end = strstr(namestr, "]");
			String c(s + 1, end - s);
			count = atoi(c.c_str());
		}

		if (IsTypeStringResource(typeString))
		{
			GLShaderResourceDeclaration* declaration = new GLShaderResourceDeclaration(GLShaderResourceDeclaration::StringToType(typeString), name, count);
			m_Resources.push_back(declaration);
		}
		else
		{
			GLShaderUniformDeclaration::Type t = GLShaderUniformDeclaration::StringToType(typeString);
			GLShaderUniformDeclaration* declaration = nullptr;

			if (t == GLShaderUniformDeclaration::Type::NONE)
			{
				// Find struct
				ShaderStruct* s = FindStruct(typeString);
				assert(s);
				declaration = new GLShaderUniformDeclaration(s, name, count);
			}
			else
			{
				declaration = new GLShaderUniformDeclaration(t, name, count);
			}

			if (StartsWith(name, "sys_"))
			{
				if (shaderType == 0)
					((GLShaderUniformBufferDeclaration*)m_VSUniformBuffers.front())->PushUniform(declaration);
				else if (shaderType == 1)
					((GLShaderUniformBufferDeclaration*)m_PSUniformBuffers.front())->PushUniform(declaration);
			}
			else
			{
				if (shaderType == 0)
				{
					if (m_VSUserUniformBuffer == nullptr)
						m_VSUserUniformBuffer = new GLShaderUniformBufferDeclaration("", 0);

					m_VSUserUniformBuffer->PushUniform(declaration);
				}
				else if (shaderType == 1)
				{
					if (m_PSUserUniformBuffer == nullptr)
						m_PSUserUniformBuffer = new GLShaderUniformBufferDeclaration("", 1);

					m_PSUserUniformBuffer->PushUniform(declaration);
				}
			}
		}
	}

	void GLShader::ParseUniformStruct(const String& block, uint shaderType)
	{
		std::vector<String> tokens = Tokenize(block);

		uint index = 0;
		index++; // struct
		String name = tokens[index++];
		ShaderStruct* uniformStruct = new ShaderStruct(name);
		index++; // {
		while (index < tokens.size())
		{
			if (tokens[index] == "}")
				break;

			String type = tokens[index++];
			String name = tokens[index++];

			// Strip ; from name if present
			if (const char* s = strstr(name.c_str(), ";"))
				name = String(name.c_str(), s - name.c_str());

			uint count = 1;
			const char* namestr = name.c_str();
			if (const char* s = strstr(namestr, "["))
			{
				name = String(namestr, s - namestr);

				const char* end = strstr(namestr, "]");
				String c(s + 1, end - s);
				count = atoi(c.c_str());
			}
			ShaderUniformDeclaration* field = new GLShaderUniformDeclaration(GLShaderUniformDeclaration::StringToType(type), name, count);
			uniformStruct->AddField(field);
		}
		m_Structs.push_back(uniformStruct);
	}

	bool GLShader::IsTypeStringResource(const String& type)
	{
		if (type == "sampler2D")		return true;
		if (type == "samplerCube")		return true;
		if (type == "sampler2DShadow")	return true;
		return false;
	}

	void GLShader::ResolveUniforms()
	{
		Bind();

		for (uint i = 0; i < m_VSUniformBuffers.size(); i++)
		{
			GLShaderUniformBufferDeclaration* decl = (GLShaderUniformBufferDeclaration*)m_VSUniformBuffers[i];
			const ShaderUniformList& uniforms = decl->GetUniformDeclarations();
			for (uint j = 0; j < uniforms.size(); j++)
			{
				GLShaderUniformDeclaration* uniform = (GLShaderUniformDeclaration*)uniforms[j];
				if (uniform->GetType() == GLShaderUniformDeclaration::Type::STRUCT)
				{
					const ShaderStruct& s = uniform->GetShaderUniformStruct();
					const auto& fields = s.GetFields();
					for (uint k = 0; k < fields.size(); k++)
					{
						GLShaderUniformDeclaration* field = (GLShaderUniformDeclaration*)fields[k];
						field->m_Location = GetUniformLocation(uniform->m_Name + "." + field->m_Name);
					}
				}
				else
				{
					uniform->m_Location = GetUniformLocation(uniform->m_Name);
				}
			}

			for (uint i = 0; i < m_PSUniformBuffers.size(); i++)
			{
				GLShaderUniformBufferDeclaration* decl = (GLShaderUniformBufferDeclaration*)m_PSUniformBuffers[i];
				const ShaderUniformList& uniforms = decl->GetUniformDeclarations();
				for (uint j = 0; j < uniforms.size(); j++)
				{
					GLShaderUniformDeclaration* uniform = (GLShaderUniformDeclaration*)uniforms[j];
					if (uniform->GetType() == GLShaderUniformDeclaration::Type::STRUCT)
					{
						const ShaderStruct& s = uniform->GetShaderUniformStruct();
						const auto& fields = s.GetFields();
						for (uint k = 0; k < fields.size(); k++)
						{
							GLShaderUniformDeclaration* field = (GLShaderUniformDeclaration*)fields[k];
							field->m_Location = GetUniformLocation(uniform->m_Name + "." + field->m_Name);
						}
					}
					else
					{
						uniform->m_Location = GetUniformLocation(uniform->m_Name);
					}
				}
			}

			{
				GLShaderUniformBufferDeclaration* decl = m_VSUserUniformBuffer;
				if (decl)
				{
					const ShaderUniformList& uniforms = decl->GetUniformDeclarations();
					for (uint j = 0; j < uniforms.size(); j++)
					{
						GLShaderUniformDeclaration* uniform = (GLShaderUniformDeclaration*)uniforms[j];
						if (uniform->GetType() == GLShaderUniformDeclaration::Type::STRUCT)
						{
							const ShaderStruct& s = uniform->GetShaderUniformStruct();
							const auto& fields = s.GetFields();
							for (uint k = 0; k < fields.size(); k++)
							{
								GLShaderUniformDeclaration* field = (GLShaderUniformDeclaration*)fields[k];
								field->m_Location = GetUniformLocation(uniform->m_Name + "." + field->m_Name);
							}
						}
						else
						{
							uniform->m_Location = GetUniformLocation(uniform->m_Name);
						}
					}
				}
			}

			{
				GLShaderUniformBufferDeclaration* decl = m_PSUserUniformBuffer;
				if (decl)
				{
					const ShaderUniformList& uniforms = decl->GetUniformDeclarations();
					for (uint j = 0; j < uniforms.size(); j++)
					{
						GLShaderUniformDeclaration* uniform = (GLShaderUniformDeclaration*)uniforms[j];
						if (uniform->GetType() == GLShaderUniformDeclaration::Type::STRUCT)
						{
							const ShaderStruct& s = uniform->GetShaderUniformStruct();
							const auto& fields = s.GetFields();
							for (uint k = 0; k < fields.size(); k++)
							{
								GLShaderUniformDeclaration* field = (GLShaderUniformDeclaration*)fields[k];
								field->m_Location = GetUniformLocation(uniform->m_Name + "." + field->m_Name);
							}
						}
						else
						{
							uniform->m_Location = GetUniformLocation(uniform->m_Name);
						}
					}
				}
			}

			uint sampler = 0;
			for (uint i = 0; i < m_Resources.size(); i++)
			{
				GLShaderResourceDeclaration* resource = (GLShaderResourceDeclaration*)m_Resources[i];
				uint location = GetUniformLocation(resource->m_Name);
				if (resource->GetCount() == 1)
				{
					resource->m_Register = sampler;
					SetUniform1i(location, sampler++);
				}
				else if (resource->GetCount() > 1)
				{
					resource->m_Register = 0;
					uint count = resource->GetCount();
					int32* samplers = new int32[count];
					for (uint s = 0; s < count; s++)
						samplers[s] = s;
					SetUniform1iv(resource->GetName(), samplers, count);
					delete[] samplers;
				}
			}
			Unbind();
		}
	}


	void GLShader::ValidateUniforms()
	{
	/*
		if (!HasUniform(SHADER_UNIFORM_PROJECTION_MATRIX_NAME))
			std::cout << m_Name << " shader does not contain pr_matrix uniform." << std::endl;
		if (!HasUniform(SHADER_UNIFORM_VIEW_MATRIX_NAME))
			std::cout << m_Name << " shader does not contain vw_matrix uniform." << std::endl;
		if (!HasUniform(SHADER_UNIFORM_MODEL_MATRIX_NAME))
			std::cout << m_Name << " shader does not contain ml_matrix uniform." << std::endl;
		std::cout << m_Name << " shader successfully validated." << std::endl;
	*/

	}


	bool GLShader::IsSystemUniform(ShaderUniformDeclaration* uniform) const
	{
		return StartsWith(uniform->GetName(), "sys_");
	}


	GLint GLShader::GetUniformLocation(const String& name)
	{
		GLint loc = glGetUniformLocation(m_ShaderID, name.c_str());
		if (loc == -1)
		{
			std::cout << "cant find uniform in " << m_Name << " shader:" << name << " (Potentially Unused)" << std::endl;
		}
		return loc;
	}

	void GLShader::SetUniformStruct(GLShaderUniformDeclaration* uniform, byte* data, int32 offset)
	{
		const ShaderStruct& s = uniform->GetShaderUniformStruct();
		const auto& fields = s.GetFields();
		for (uint k = 0; k < fields.size(); k++)
		{
			GLShaderUniformDeclaration* field = (GLShaderUniformDeclaration*)fields[k];
			ResolveAndSetUniformField(*field, data, offset);
			offset += field->m_Size;
		}
	}

	ShaderUniformDeclaration* GLShader::FindUniformDeclaration(const String& name, const ShaderUniformBufferDeclaration* buffer)
	{
		const ShaderUniformList& uniforms = buffer->GetUniformDeclarations();
		for (uint i = 0; i < uniforms.size(); i++)
		{
			if (uniforms[i]->GetName() == name)
				return uniforms[i];
		}
		return nullptr;
	}

	ShaderUniformDeclaration* GLShader::FindUniformDeclaration(const String& name)
	{
		ShaderUniformDeclaration* result = nullptr;
		for (uint i = 0; i < m_VSUniformBuffers.size(); i++)
		{
			result = FindUniformDeclaration(name, m_VSUniformBuffers[i]);
			if (result)
				return result;
		}

		for (uint i = 0; i < m_PSUniformBuffers.size(); i++)
		{
			result = FindUniformDeclaration(name, m_PSUniformBuffers[i]);
			if (result)
				return result;
		}

		result = FindUniformDeclaration(name, m_VSUserUniformBuffer);
		if (result)
			return result;

		result = FindUniformDeclaration(name, m_PSUserUniformBuffer);
		if (result)
			return result;

		return result;
	}


	void GLShader::SetVSSystemUniformBuffer(byte* data, uint size, uint slot)
	{
		Bind();
		assert(m_VSUniformBuffers.size() > slot);
		ShaderUniformBufferDeclaration* declaration = m_VSUniformBuffers[slot];
		ResolveAndSetUniforms(declaration, data, size);
	}

	void GLShader::SetPSSystemUniformBuffer(byte* data, uint size, uint slot)
	{
		Bind();
		assert(m_PSUniformBuffers.size() > slot);
		ShaderUniformBufferDeclaration* declaration = m_PSUniformBuffers[slot];
		ResolveAndSetUniforms(declaration, data, size);
	}

	void GLShader::SetVSUserUniformBuffer(byte* data, uint size)
	{
		ResolveAndSetUniforms(m_VSUserUniformBuffer, data, size);
	}

	void GLShader::SetPSUserUniformBuffer(byte* data, uint size)
	{
		ResolveAndSetUniforms(m_PSUserUniformBuffer, data, size);
	}

	ShaderStruct* GLShader::FindStruct(const String& name)
	{
		for (ShaderStruct* s : m_Structs)
		{
			if (s->GetName() == name)
				return s;
		}
		return nullptr;
	}

	void GLShader::ResolveAndSetUniforms(ShaderUniformBufferDeclaration* buffer, byte* data, uint size)
	{
		const ShaderUniformList& uniforms = buffer->GetUniformDeclarations();
		for (uint i = 0; i < uniforms.size(); i++)
		{
			GLShaderUniformDeclaration* uniform = (GLShaderUniformDeclaration*)uniforms[i];
			ResolveAndSetUniform(uniform, data, size);
		}
	}

	void GLShader::ResolveAndSetUniform(GLShaderUniformDeclaration* uniform, byte* data, uint size)
	{

		if (uniform->GetLocation() == -1)
			return;

		uint offset = uniform->GetOffset();

		switch (uniform->GetType())
		{
		case GLShaderUniformDeclaration::Type::FLOAT32:
			SetUniform1f(uniform->GetLocation(), *(float*)&data[offset]);
			break;
		case GLShaderUniformDeclaration::Type::INT32:
			SetUniform1i(uniform->GetLocation(), *(int*)&data[offset]);
			break;
		case GLShaderUniformDeclaration::Type::VEC2:
			SetUniform2f(uniform->GetLocation(), *(glm::vec2*)&data[offset]);
			break;
		case GLShaderUniformDeclaration::Type::VEC3:
			SetUniform3f(uniform->GetLocation(), *(glm::vec3*)&data[offset]);
			break;
		case GLShaderUniformDeclaration::Type::VEC4:
			SetUniform4f(uniform->GetLocation(), *(glm::vec4*)&data[offset]);
			break;
		case GLShaderUniformDeclaration::Type::MAT3:
			// TODO: SetUniformMat3(uniform->GetLocation(), *(glm::mat3*)&data[offset]);
			break;
		case GLShaderUniformDeclaration::Type::MAT4:
			SetUniformMat4(uniform->GetLocation(), *(glm::mat4*)&data[offset]);
			break;
		case GLShaderUniformDeclaration::Type::STRUCT:
			SetUniformStruct(uniform, data, offset);
			break;
		default:
			std::cout << "Unknown type!" << std::endl;
			assert(false);

		}
	}

	void GLShader::SetUniform(const String& name, byte* data)
	{
		ShaderUniformDeclaration* uniform = FindUniformDeclaration(name);
		if (!uniform)
		{
			std::cout << "Cannot find uniform in " << m_Name << " shader with name '" << name << "'" << std::endl;
			return;
		}
		ResolveAndSetUniform((GLShaderUniformDeclaration*)uniform, data, 0);
	}

	void GLShader::ResolveAndSetUniformField(const GLShaderUniformDeclaration& field, byte* data, int32 offset)
	{
		switch (field.GetType())
		{
		case GLShaderUniformDeclaration::Type::FLOAT32:
			SetUniform1f(field.GetLocation(), *(float*)&data[offset]);
			break;
		case GLShaderUniformDeclaration::Type::INT32:
			SetUniform1i(field.GetLocation(), *(int32*)&data[offset]);
			break;
		case GLShaderUniformDeclaration::Type::VEC2:
			SetUniform2f(field.GetLocation(), *(glm::vec2*)&data[offset]);
			break;
		case GLShaderUniformDeclaration::Type::VEC3:
			SetUniform3f(field.GetLocation(), *(glm::vec3*)&data[offset]);
			break;
		case GLShaderUniformDeclaration::Type::VEC4:
			SetUniform4f(field.GetLocation(), *(glm::vec4*)&data[offset]);
			break;
		case GLShaderUniformDeclaration::Type::MAT3:
			// TODO: SetUniformMat3(field.location, *(glm::mat3*)&data[offset]);
			break;
		case GLShaderUniformDeclaration::Type::MAT4:
			SetUniformMat4(field.GetLocation(), *(glm::mat4*)&data[offset]);
			break;
		default:
			std::cout << "Unknown type!" << std::endl;
			assert(false);
		}
	}




	void GLShader::SetUniform1f(const String& name, float value)
	{
		SetUniform1f(GetUniformLocation(name), value);
	}

	void GLShader::SetUniform1fv(const String& name, float* value, int32 count)
	{
		SetUniform1fv(GetUniformLocation(name), value, count);
	}

	void GLShader::SetUniform1i(const String& name, int32 value)
	{
		SetUniform1i(GetUniformLocation(name), value);
	}

	void GLShader::SetUniform1iv(const String& name, int32* value, int32 count)
	{
		SetUniform1iv(GetUniformLocation(name), value, count);
	}

	void GLShader::SetUniform2f(const String& name, const glm::vec2& vector)
	{
		SetUniform2f(GetUniformLocation(name), vector);
	}

	void GLShader::SetUniform3f(const String& name, const glm::vec3& vector)
	{
		SetUniform3f(GetUniformLocation(name), vector);
	}

	void GLShader::SetUniform4f(const String& name, const glm::vec4& vector)
	{
		SetUniform4f(GetUniformLocation(name), vector);
	}

	void GLShader::SetUniformMat4(const String& name, const glm::mat4& matrix)
	{
		SetUniformMat4(GetUniformLocation(name), matrix);
	}

	void GLShader::SetUniform1f(uint location, float value)
	{
		glUniform1f(location, value);
	}

	void GLShader::SetUniform1fv(uint location, float* value, int32 count)
	{
		glUniform1fv(location, count, value);
	}

	void GLShader::SetUniform1i(uint location, int32 value)
	{
		glUniform1i(location, value);
	}

	void GLShader::SetUniform1iv(uint location, int32* value, int32 count)
	{
		glUniform1iv(location, count, value);
	}

	void GLShader::SetUniform2f(uint location, const glm::vec2& vector)
	{
		glUniform2f(location, vector.x, vector.y);
	}

	void GLShader::SetUniform3f(uint location, const glm::vec3& vector)
	{
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void GLShader::SetUniform4f(uint location, const glm::vec4& vector)
	{
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}

	void GLShader::SetUniformMat4(uint location, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(location, 1, GL_TRUE, &matrix[0][0]);
	}
