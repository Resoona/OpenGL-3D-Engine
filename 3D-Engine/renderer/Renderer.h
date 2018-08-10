#pragma once
#include "../graphics/StaticSprite.h"

#include <deque>

class Renderer
{
private:
	std::deque<StaticSprite*> m_RenderQueue;

public:
	void submit(StaticSprite* sprite);
	void flush();
};
