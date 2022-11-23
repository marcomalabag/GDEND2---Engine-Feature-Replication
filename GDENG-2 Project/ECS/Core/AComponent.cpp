#include "AComponent.h"

#include "ECS/GameObject/AGameObject.h"

AComponent::AComponent(AGameObject& owner) :
	ownerRef{owner}
{
}

AComponent::~AComponent() = default;

AGameObject& AComponent::getOwner() const
{
	return ownerRef;
}

bool AComponent::operator==(const AComponent& other) const
{
	return getName() == other.getName() &&
	       ownerRef.Name == other.getOwner().Name;
}

bool AComponent::operator!=(const AComponent& other) const
{
	return getName() != other.getName() ||
	       ownerRef.Name != other.getOwner().Name;
}
