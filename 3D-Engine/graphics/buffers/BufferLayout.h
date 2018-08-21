#pragma once


#include <vector>
#include <glm/glm.hpp>

#include <GL/glew.h>
typedef std::string String;
typedef GLuint uint;

struct BufferLayoutType
{	
	String name;
	uint type;
	uint size;
	uint count;
	uint offset;
	bool normalized;
};
class BufferLayout
{
private:
	GLuint m_Size;
	std::vector<BufferLayoutType> m_Layout;
public:
	BufferLayout();

	template<typename T>
	void Push(const String& name, uint count = 1, bool normalized = false)
	{
		assert(false);
	}

	template<> void Push<float>(const String& name, uint count, bool normalized) { Push(name, GL_FLOAT, sizeof(float) * count, count, normalized); }
	template<> void Push<uint>(const String& name, uint count, bool normalized) { Push(name, GL_UNSIGNED_INT, sizeof(uint) * count, count, normalized); }
	template<> void Push<GLbyte>(const String& name, uint count, bool normalized) { Push(name, GL_UNSIGNED_BYTE, sizeof(GLbyte) * count, count, normalized); }
	template<> void Push<glm::vec2>(const String& name, uint count, bool normalized) { Push(name, GL_FLOAT, sizeof(glm::vec2) * count, 2 * count, normalized); }
	template<> void Push<glm::vec3>(const String& name, uint count, bool normalized) { Push(name, GL_FLOAT, sizeof(glm::vec3) * count, 3 * count, normalized); }
	template<> void Push<glm::vec4>(const String& name, uint count, bool normalized) { Push(name, GL_FLOAT, sizeof(glm::vec4) * count, 4 * count, normalized); }

	inline const std::vector<BufferLayoutType>& GetLayout() const { return m_Layout; }
	inline uint GetStride() const { return m_Size; }
private:
	void Push(const String& name, uint type, uint size, uint count, bool normalized);
};
