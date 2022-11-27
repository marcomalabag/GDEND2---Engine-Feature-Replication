#pragma once

#include "ECS/Component/RenderComponent.h"
#include "ECS/System/RenderSystem.h"

class SystemManager final
{
public:
	static void initialize();
	static void terminate();

	~SystemManager();

	static SystemManager& getInstance();

	template <typename ComponentType>
	void registerComponent(ComponentType* component);

	template <typename T>
	void deregisterComponent(AGameObject& gameObjRef);

	RenderSystem& getRenderSystem() const;
	// CameraSystem& getCameraSystem() const;

	SystemManager(const SystemManager&)                = delete;
	SystemManager& operator=(const SystemManager&)     = delete;
	SystemManager(SystemManager&&) noexcept            = delete;
	SystemManager& operator=(SystemManager&&) noexcept = delete;

private:
	SystemManager();

	static SystemManager* instance;

	RenderSystem* renderSystem;
	// CameraSystem* cameraSystem;
};

//---- REGISTER COMPONENT
template <typename ComponentType>
void SystemManager::registerComponent(ComponentType* component)
{
	Debug::Log("Please add an implementation to registerComponent() for {0} component in SystemHandler!",
	           ComponentType::getStaticName());
}

template <>
inline void SystemManager::registerComponent<RenderComponent>(RenderComponent* component)
{
	renderSystem->registerComponent(component);
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