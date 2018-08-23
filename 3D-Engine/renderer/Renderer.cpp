#include "Renderer.h"
#include <glm/gtc/matrix_transform.inl>

void Renderer::submit(StaticSprite* sprite)
{
	m_RenderQueue.push_back(sprite);
}

void Renderer::flush()
{
	while (!m_RenderQueue.empty())
	{
		StaticSprite* sprite = m_RenderQueue.front();

		sprite->getVAO()->Bind();
		sprite->getIBO()->Bind();

		sprite->getShader().Bind();
		sprite->getShader().SetUniformMat4("M", glm::translate(glm::mat4(), *sprite->getPosition()));

		glBindTexture(GL_TEXTURE_2D, sprite->getTextureID());

		glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

		sprite->getShader().Unbind();

		sprite->getIBO()->Unbind();
		sprite->getVAO()->Unbind();

		m_RenderQueue.pop_front();
	}
}