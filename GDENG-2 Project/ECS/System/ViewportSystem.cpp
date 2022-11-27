#include "ViewportSystem.h"

ViewportSystem::ViewportSystem() {}

ViewportSystem::~ViewportSystem() {}

void ViewportSystem::registerViewport(ViewportScreen* component) {}

void ViewportSystem::deregisterViewport(UIID viewportHandle) {}

ViewportScreen* ViewportSystem::getViewport(UIID viewportHandle)
{
	return nullptr;
}
