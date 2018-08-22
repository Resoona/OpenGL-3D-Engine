#include "Renderer.h"

void Renderer::submit(StaticSprite* sprite)
{
	m_RenderQueue.push_back(sprite);
}

void Renderer::flush()
{
	while (!m_RenderQueue.empty())
	{
		StaticSprite* sprite = m_RenderQueue.front();

		sprite->getVAO()->bind();
		sprite->getIBO()->bind();

		sprite->getShader().Bind();
		sprite->getShader().SetUniformMat4("M", glm::translate(glm::mat4(), *sprite->getPosition()));

		glBindTexture(GL_TEXTURE_2D, sprite->getTextureID());

		glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

		sprite->getShader().Unbind();

		sprite->getIBO()->unbind();
		sprite->getVAO()->unbind();

		m_RenderQueue.pop_front();
	}
}