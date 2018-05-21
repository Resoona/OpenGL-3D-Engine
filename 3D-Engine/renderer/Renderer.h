#pragma once
#include "../graphics/StaticSprite.h"

#include <deque>

class Renderer
{
private:
	std::deque<const StaticSprite*> m_RenderQueue;

public:
	void submit(const StaticSprite* sprite);
	void flush();
};
