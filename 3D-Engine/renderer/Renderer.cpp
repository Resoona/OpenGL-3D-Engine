#include "Renderer.h"

void Renderer::submit(const StaticSprite* sprite)
{
	m_RenderQueue.push_back(sprite);
}

void Renderer::flush()
{
	while (!m_RenderQueue.empty())
	{
		const StaticSprite* sprite = m_RenderQueue.front();

		sprite->getVAO()->bind();
		sprite->getIBO()->bind();

		sprite->getShader().setUniformMat4("M", glm::translate(glm::mat4(), *sprite->getPosition()));

		glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

		sprite->getIBO()->unbind();
		sprite->getVAO()->unbind();

		m_RenderQueue.pop_front();

	}
	

}
