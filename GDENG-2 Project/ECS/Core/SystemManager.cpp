#include "SystemManager.h"

#include "Debug.h"

SystemManager* SystemManager::instance = nullptr;

void SystemManager::initialize()
{
	if (instance == nullptr)
	{
		instance = new SystemManager();
	}
}

void SystemManager::terminate()
{
	delete instance;
}

SystemManager::SystemManager()
{
	// Init all respective systems
	renderSystem = new RenderSystem();
}

SystemManager::~SystemManager()
{
}

SystemManager& SystemManager::getInstance()
{
	Debug::Assert(instance != nullptr,
			  "SystemHandler must be initialized first using init()!");

	return *instance;
}

RenderSystem& SystemManager::getRenderSystem() const
{
	return *renderSystem;
}

