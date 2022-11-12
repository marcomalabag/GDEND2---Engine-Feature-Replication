#include "EditorViewportScreen.h"

#include "Graphics/GraphicsEngine.h"
#include "Graphics/SwapChain.h"

EditorViewportScreen::EditorViewportScreen() :
	AViewportScreen{"EditorViewportScreen"}
{
}

EditorViewportScreen::~EditorViewportScreen()
{
}

Framebuffer& EditorViewportScreen::getFramebufferRef()
{
	return GraphicsEngine::getInstance()->getSwapChain().getBuffer();
}
