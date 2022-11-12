#pragma once
#include <unordered_map>

#include "Debug.h"

#include "System/SystemHandler.h"

//Remember:
//GameObject is an ID
//Components are Data
//Systems are DataProcessors

class AComponent;
class TransformComponent;
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

	TransformComponent& transform() const;

	// TODO: What to do for copying
	// Idea is that all component's data will be copied
	AGameObject(const AGameObject&) = delete;

	AGameObject& operator=(const AGameObject& v) = delete;

	AGameObject(AGameObject&&) noexcept = delete;

	AGameObject& operator=(AGameObject&&) noexcept = delete;

	std::string Name;

private:
	TransformComponent* localTransform;
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
