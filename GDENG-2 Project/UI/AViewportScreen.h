#pragma once
#include "AUIScreen.h"

class Framebuffer;
class AViewportScreen : public AUIScreen
{
public:
	explicit AViewportScreen(UILabel viewportID);
	~AViewportScreen() override;
	
protected:
	void drawUI() override;
	
	
	virtual Framebuffer& getFramebufferRef() = 0;

private:
	Framebuffer* framebufferRef = nullptr;
};

