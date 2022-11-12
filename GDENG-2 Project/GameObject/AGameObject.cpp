#include "AGameObject.h"

#include "Component/TransformComponent.h"

AGameObject::AGameObject(const std::string_view name) :
	Name(name),
	localTransform{new TransformComponent(*this)}
{
}

AGameObject::~AGameObject()
{
	delete localTransform;
}

TransformComponent& AGameObject::transform() const
{
	return *localTransform;
}
