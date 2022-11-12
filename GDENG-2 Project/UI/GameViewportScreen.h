#pragma once
#include "AViewportScreen.h"

class GameViewportScreen final : public AViewportScreen
{
public:
	GameViewportScreen();
	~GameViewportScreen() override;
protected:
	Framebuffer& getFramebufferRef() override;
};
