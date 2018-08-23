#include "TransformComponent.h"

namespace entity {
	namespace component {
		TransformComponent::TransformComponent(const glm::mat4& transform)
			: transform(transform)
		{
		}
	}
}