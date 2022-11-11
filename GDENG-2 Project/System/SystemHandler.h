#pragma once

#include "Component/RenderComponent.h"

#include "RenderSystem.h"

class SystemHandler final
{
public:
	static void init();
	static void release();

	~SystemHandler();

	static SystemHandler& getInstance();

	template <typename T>
	T& registerComponent(AGameObject& gameObjRef,
	                     T& component);

	template <typename T>
	void deregisterComponent(AGameObject& gameObjRef);

	template <typename T>
	T* getComponent(AGameObject& gameObjRef);

	SystemHandler(const SystemHandler&)                = delete;
	SystemHandler& operator=(const SystemHandler&)     = delete;
	SystemHandler(SystemHandler&&) noexcept            = delete;
	SystemHandler& operator=(SystemHandler&&) noexcept = delete;

private:
	SystemHandler();

	static SystemHandler* instance;

	RenderSystem* m_RenderSystem;
};

//---- REGISTER COMPONENT
template <typename T>
T& SystemHandler::registerComponent(AGameObject& gameObjRef,
                                    T& component)
{
	Debug::Log("Please add an implementation to registerComponent() for {0} component in SystemHandler!",
	           T::getStaticName());
	return T();
}

template <>
inline RenderComponent& SystemHandler::registerComponent<RenderComponent>(AGameObject& gameObjRef,
                                                                          RenderComponent& component)
{
	return m_RenderSystem->registerComponent(gameObjRef, component);
}

//---- DEREGISTER COMPONENT
template <typename T>
void SystemHandler::deregisterComponent(AGameObject& gameObjRef)
{
	Debug::Log("Please add an implementation to deregisterComponent() for {0} component in SystemHandler!",
	           T::getStaticName());
}

template <>
inline void SystemHandler::deregisterComponent<RenderComponent>(AGameObject& gameObjRef)
{
	m_RenderSystem->deregisterComponent(gameObjRef);
}

//---- GET COMPONENT
template <typename T>
T* SystemHandler::getComponent(AGameObject& gameObjRef)
{
	Debug::Log("Please add an implementation to getComponent() for {0} component in SystemHandler!",
	           T::getStaticName());
	return nullptr;
}

template <>
inline RenderComponent* SystemHandler::getComponent<RenderComponent>(AGameObject& gameObjRef)
{
	return m_RenderSystem->getComponent(gameObjRef);
}
