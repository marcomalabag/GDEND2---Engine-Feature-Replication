#include "EditorViewportScreen.h"

#include "SceneCameraHandler.h"

EditorViewportScreen::EditorViewportScreen() :
	AViewportScreen{"EditorViewportScreen"}
{
}

EditorViewportScreen::~EditorViewportScreen()
{
}

Framebuffer& EditorViewportScreen::getFramebufferRef()
{
	return *SceneCameraHandler::getInstance()->getFramebuffer();
}
