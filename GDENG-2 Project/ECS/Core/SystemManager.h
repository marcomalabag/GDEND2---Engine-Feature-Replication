#pragma once

#include "ECS/Component/RenderComponent.h"

#include "ECS/System/RenderSystem.h"

class SystemManager final
{
public:
	static void init();
	static void release();

	~SystemManager();

	static SystemManager& getInstance();

	template <typename ComponentType, typename... Args>
	ComponentType& createComponent(Args&&...args);

	template <typename T>
	T& registerComponent(AGameObject& gameObjRef,
	                     T& component);

	template <typename T>
	void deregisterComponent(AGameObject& gameObjRef);

	template <typename T>
	T* getComponent(AGameObject& gameObjRef);

	[[nodiscard]]
	RenderSystem& getRenderSystem() const;

	SystemManager(const SystemManager&)                = delete;
	SystemManager& operator=(const SystemManager&)     = delete;
	SystemManager(SystemManager&&) noexcept            = delete;
	SystemManager& operator=(SystemManager&&) noexcept = delete;

private:
	SystemManager();

	static SystemManager* instance;

	// TransformSystem
	
	RenderSystem* renderSystem;
};

//---- REGISTER COMPONENT
template <typename T>
T& SystemManager::registerComponent(AGameObject& gameObjRef,
                                    T& component)
{
	Debug::Log("Please add an implementation to registerComponent() for {0} component in SystemHandler!",
	           T::getStaticName());
	return T();
}

template <>
inline RenderComponent& SystemManager::registerComponent<RenderComponent>(AGameObject& gameObjRef,
                                                                          RenderComponent& component)
{
	return renderSystem->registerComponent(gameObjRef, component);
}

//---- DEREGISTER COMPONENT
template <typename T>
void SystemManager::deregisterComponent(AGameObject& gameObjRef)
{
	Debug::Log("Please add an implementation to deregisterComponent() for {0} component in SystemHandler!",
	           T::getStaticName());
}

template <>
inline void SystemManager::deregisterComponent<RenderComponent>(AGameObject& gameObjRef)
{
	renderSystem->deregisterComponent(gameObjRef);
}

//---- GET COMPONENT
template <typename T>
T* SystemManager::getComponent(AGameObject& gameObjRef)
{
	Debug::Log("Please add an implementation to getComponent() for {0} component in SystemHandler!",
	           T::getStaticName());
	return nullptr;
}

template <>
inline RenderComponent* SystemManager::getComponent<RenderComponent>(AGameObject& gameObjRef)
{
	return renderSystem->getComponent(gameObjRef);
}
