#pragma once
#include "Debug.h"
#include "GameObjectManager.h"
#include "SystemManager.h"

class AGameObject
{
public:
	explicit AGameObject(std::string_view name);

	virtual ~AGameObject();

	template <typename ComponentType, typename... Args>
	ComponentType& attachComponent(Args&&... args);

	template <typename ComponentType>
	void detachComponent();

	template <class ComponentType>
	ComponentType* getComponent();

	// TODO: What to do for copying
	// Idea is that all component's data will be copied
	AGameObject(const AGameObject&)                = delete;
	AGameObject& operator=(const AGameObject&)     = delete;
	AGameObject(AGameObject&&) noexcept            = delete;
	AGameObject& operator=(AGameObject&&) noexcept = delete;

	std::string Name; // Might return to private due to need to keep track since this is an ID
};

template <typename ComponentType, typename ... Args>
ComponentType& AGameObject::attachComponent(Args&&... args)
{
	if (GameObjectManager::getInstance()->hasComponent(this, ComponentType::getStaticName()))
	{
		return GameObjectManager::getInstance()->getComponent(this, ComponentType::getStaticName());
	}

	ComponentType* newComponent = new ComponentType(*this, std::forward<Args>(args)...);
	newComponent = GameObjectManager::getInstance()->attachComponent(this, newComponent);

	SystemManager::getInstance().registerComponent<ComponentType>(newComponent);
	return newComponent;
}

template <typename ComponentType>
void AGameObject::detachComponent()
{
	const AComponent* hasComponent = GameObjectManager::getInstance()->getComponent(this,
	                                                                                ComponentType::getStaticName());
	if (hasComponent == nullptr)
	{
		return;
	}
	
	SystemManager::getInstance().deregisterComponent<ComponentType>(*this);
	GameObjectManager::getInstance()->detachComponent(this, hasComponent);
}

template <class ComponentType>
ComponentType* AGameObject::getComponent()
{
	return GameObjectManager::getInstance()->getComponent(this,
	                                                      ComponentType::getStaticName());
}
