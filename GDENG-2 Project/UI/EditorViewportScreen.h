#pragma once
#include "AViewportScreen.h"

class EditorViewportScreen final : public AViewportScreen
{
public:
	EditorViewportScreen();
	~EditorViewportScreen() override;
protected:
	Framebuffer& getFramebufferRef() override;
};
