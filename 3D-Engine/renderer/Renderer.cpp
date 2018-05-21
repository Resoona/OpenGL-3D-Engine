﻿#include "Renderer.h"

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

		sprite->getShader().enable();
		sprite->getShader().setUniformMat4("M", glm::translate(glm::mat4(), *sprite->getPosition()));

		glBindTexture(GL_TEXTURE_2D, sprite->getTextureID());

		glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

		sprite->getShader().disable();

		sprite->getIBO()->unbind();
		sprite->getVAO()->unbind();

		m_RenderQueue.pop_front();
	}
}