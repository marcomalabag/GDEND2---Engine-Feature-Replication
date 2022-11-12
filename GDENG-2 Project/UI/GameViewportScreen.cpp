#include "GameViewportScreen.h"

#include "GameCameraHandler.h"

GameViewportScreen::GameViewportScreen() :
	AViewportScreen{"GameViewportScreen"}
{
}

GameViewportScreen::~GameViewportScreen()
{
}

Framebuffer& GameViewportScreen::getFramebufferRef()
{
	return *GameCameraHandler::getInstance()->getFramebuffer();
}
