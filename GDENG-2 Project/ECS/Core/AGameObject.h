#pragma once
#include <unordered_map>

#include "Debug.h"

#include "SystemHandler.h"

//Remember:
//GameObject is an ID
//Components are Data
//Systems are DataProcessors

class AComponent;
class AGameObject
{
public:
	explicit AGameObject(std::string_view name);

	virtual ~AGameObject();

	template <typename T, typename... Args>
	T& attachComponent(Args&&... args);

	template <typename T>
	void detachComponent();

	template <class T>
	T* getComponent();

	// TODO: What to do for copying
	// Idea is that all component's data will be copied
	AGameObject(const AGameObject&)                = delete;
	AGameObject& operator=(const AGameObject&)     = delete;
	AGameObject(AGameObject&&) noexcept            = delete;
	AGameObject& operator=(AGameObject&&) noexcept = delete;

	std::string Name;
};

template <typename T, typename ... Args>
T& AGameObject::attachComponent(Args&&... args)
{
	T* component = new T(std::forward<Args>(args)...);
	return SystemHandler::getInstance().registerComponent<T>(*this, *component);
}

template <typename T>
void AGameObject::detachComponent()
{
	SystemHandler::getInstance().deregisterComponent<T>(*this);
}

template <class T>
T* AGameObject::getComponent()
{
	return SystemHandler::getInstance().getComponent<T>(*this);
}
