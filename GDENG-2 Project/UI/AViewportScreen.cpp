#include "AViewportScreen.h"

#include "Graphics/Framebuffer.h"

#include "IMGUI/imgui.h"

AViewportScreen::AViewportScreen(UILabel viewportID) :
	AUIScreen{viewportID}
{
}

AViewportScreen::~AViewportScreen()
{
}

void AViewportScreen::drawUI()
{
	ImGui::Begin(name.c_str());

	if (framebufferRef != nullptr)
	{
		ImGui::Image(&framebufferRef->getFrame(),
		             ImVec2(16 * 10, 9 * 10));
	}
	ImGui::Text("Placeholder");

	ImGui::End();
}
