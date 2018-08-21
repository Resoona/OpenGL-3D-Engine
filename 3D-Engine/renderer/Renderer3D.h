#pragma once
#include "../graphics/Mesh.h"

//
// Base class for all 3D renderers.
// 
// Implementations:
//		- ForwardRenderer.h  (WIP)
//		- DeferredRenderer.h (TBA)
//
class Renderer3D
{
protected:
	std::vector<Mesh*> m_DrawQueue;
public:
	virtual void Init() = 0;
	virtual void Begin() = 0;
	virtual void Submit(Mesh* mesh) = 0;
	virtual void End() = 0;
	virtual void Present() = 0;

};
