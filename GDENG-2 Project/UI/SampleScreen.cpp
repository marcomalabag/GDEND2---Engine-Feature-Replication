#include "SampleScreen.h"

SampleScreen::SampleScreen(UIID uiScreenID) :
	AUIScreen{uiScreenID, "SampleScreen"} {}
SampleScreen::~SampleScreen() = default;

void SampleScreen::drawUI()
{
	ImGui::Begin(this->getNameAndIDLabel());

	ImGui::Text("Testing UI Rendering!");
	ImGui::End();
}
