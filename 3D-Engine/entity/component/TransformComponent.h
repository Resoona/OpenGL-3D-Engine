#pragma once

#include "Component.h"
#include <glm/glm.hpp>

namespace entity {
	namespace component {
		class TransformComponent : public Component
		{
		public:
			glm::mat4 transform;
		public:
			TransformComponent(const glm::mat4& transform);
			static ComponentType* GetStaticType()
			{
				static ComponentType type({ "Transform" });
				return &type;
			}
			inline virtual ComponentType* GetType() const override { return GetStaticType(); }
		};
	}
}