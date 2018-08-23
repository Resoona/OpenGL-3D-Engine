#pragma once
#include "Component.h"

#include "../../graphics/Mesh.h"

namespace entity {
	namespace component {
		class MeshComponent : public Component
		{
		public:
			Mesh* mesh;
			MeshComponent(Mesh* mesh);

			static ComponentType* GetStaticType()
			{
				static ComponentType type({ "Mesh" });
				return &type;
			}

			inline virtual ComponentType* GetType() const override { return GetStaticType(); }
		};
	}
}
