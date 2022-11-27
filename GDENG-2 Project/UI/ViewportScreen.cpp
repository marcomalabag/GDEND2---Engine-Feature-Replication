#include "ViewportScreen.h"

ViewportScreen::ViewportScreen(UIID viewportID) :
	AUIScreen{viewportID, "Viewport"} {}

ViewportScreen::~ViewportScreen() {}

void ViewportScreen::drawUI()
{
	ImGui::Begin(this->getNameAndIDLabel());

	if (ImGui::IsWindowFocused())
	{
		ImGui::Text("This is viewport Focused!");
		// Send camera id to the Camera system
	}
	else
	{
		ImGui::Text("This is viewport UnFocused!");
	}
	
	
	ImGui::End();
}
