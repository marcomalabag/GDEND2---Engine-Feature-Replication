#include "CreditsScreen.h"

CreditsScreen::CreditsScreen():AUIScreen("Credits Screen")
{
}

void CreditsScreen::drawUI()
{
	ImGui::Begin("Credits");
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 1125, 25));
	ImGui::SetWindowSize(ImVec2(550, UIManager::WINDOW_HEIGHT - 550));
	ImGui::Text("About\n");

	if(ImGui::Button("Close"))
	{
		
	}
	ImGui::End();
}

CreditsScreen::~CreditsScreen()
{
}


