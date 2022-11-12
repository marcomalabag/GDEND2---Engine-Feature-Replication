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

	framebufferRef = &this->getFramebufferRef();
	if (framebufferRef != nullptr)
	{
		// TODO: Resizing viewports
		ImGui::Image(&framebufferRef->getFrame(),
		             ImVec2(16 * 40, 9 * 40));
	}
	ImGui::Text("Placeholder");

	ImGui::End();
}
