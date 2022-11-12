#include "GameViewportScreen.h"

#include "Graphics/GraphicsEngine.h"
#include "Graphics/SwapChain.h"

GameViewportScreen::GameViewportScreen() :
	AViewportScreen{"GameViewportScreen"}
{
}

GameViewportScreen::~GameViewportScreen()
{
}

Framebuffer& GameViewportScreen::getFramebufferRef()
{
	return GraphicsEngine::getInstance()->getSwapChain().getBuffer();
}
