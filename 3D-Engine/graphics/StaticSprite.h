#pragma once
#include "buffers/IndexBuffer.h"
#include "buffers/VertexArray.h"
#include "Texture.h"
#include "shaders/Shader.h"

class StaticSprite
{

private:
	VertexArray* m_VertexArray;
	IndexBuffer* m_IndexBuffer;
	Shader& m_Shader;
	GLuint m_textureID;

	glm::vec3* m_position;
	glm::vec3* m_size;

public:
	StaticSprite(float x, float y, float z, float width, float height, float depth, const glm::vec4& color, Shader& shader);
	StaticSprite(float x, float y, float z, float width, float height, const glm::vec4& color, Shader& shader);
	StaticSprite(float x, float y, float z, float width, float height, float depth, GLuint textureID, Shader& shader);
	StaticSprite(float x, float y, float z, std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals, std::vector<GLushort> indicies, GLuint textureID, Shader& shader);
	~StaticSprite();

	inline const VertexArray* getVAO() const { return m_VertexArray; }
	inline const IndexBuffer* getIBO() const { return m_IndexBuffer; }
	inline const GLuint getTextureID() const { return m_textureID; }
	inline Shader& getShader() const { return m_Shader; }

	inline const glm::vec3* getPosition() const { return m_position; }
	inline const glm::vec3* getSize() const { return m_size; }

	inline void setPosition(float x, float y, float z) const { *m_position = glm::vec3(x, y, z); }

	void bindArrays();
};
