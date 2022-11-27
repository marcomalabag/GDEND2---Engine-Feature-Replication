#pragma once
#include "AUIScreen.h"

class SampleScreen final : public AUIScreen
{
public:
	explicit SampleScreen(UIID uiScreenID);
	~SampleScreen() override;
protected:
	void drawUI() override;
public:
	
};
