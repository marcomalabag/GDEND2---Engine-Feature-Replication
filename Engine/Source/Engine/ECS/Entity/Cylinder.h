#pragma once
#include "Engine/ECS/Core/Entity.h"
namespace Engine
{
	class Cylinder final : public Entity
	{
		public:
			explicit Cylinder(EntityID id,
				StringView name,
				ComponentRegistry* componentRegistry);

			~Cylinder() override;
	};
};

