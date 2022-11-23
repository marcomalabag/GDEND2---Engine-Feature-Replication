#include "SystemHandler.h"

#include "Debug.h"

SystemHandler* SystemHandler::instance = nullptr;

void SystemHandler::init()
{
	if (instance == nullptr)
	{
		instance = new SystemHandler();
	}
}

void SystemHandler::release()
{
	delete instance;
}

SystemHandler::SystemHandler()
{
	// Init all respective systems
	renderSystem = new RenderSystem();
}

SystemHandler::~SystemHandler()
{
}

SystemHandler& SystemHandler::getInstance()
{
	Debug::Assert(instance != nullptr,
			  "SystemHandler must be initialized first using init()!");

	return *instance;
}
RenderSystem& SystemHandler::getRenderSystem() const
{
	return *renderSystem;
}

