#pragma once
#include "buffers/IndexBuffer.h"
#include "buffers/VertexArray.h"
#include "Texture.h"
#include "Shader.h"

class StaticSprite
{

private:
	VertexArray* m_VertexArray;
	IndexBuffer* m_IndexBuffer;
	Shader& m_Shader;

	glm::vec3* m_position;
	glm::vec3* m_size;

public:
	StaticSprite(float x, float y, float z, float width, float height, float depth, const glm::vec4& color, Shader& shader);
	StaticSprite(float x, float y, float z, float width, float height, float depth, Texture* texture, Shader& shader);
	~StaticSprite();

	inline const VertexArray* getVAO() const { return m_VertexArray; }
	inline const IndexBuffer* getIBO() const { return m_IndexBuffer; }
	inline Shader& getShader() const { return m_Shader; }

	inline const glm::vec3* getPosition() const { return m_position; }
	inline const glm::vec3* getSize() const { return m_size; }

	void bindArrays();
};
