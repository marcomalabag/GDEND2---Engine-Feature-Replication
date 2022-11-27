#pragma once
#include "AUIScreen.h"

class ViewportScreen final : public AUIScreen
{
public:
	explicit ViewportScreen(UIID viewportID);
	~ViewportScreen() override;
	
protected:
	void drawUI() override;
	
	//virtual Framebuffer& getFramebufferRef() = 0;

private:
	
};

