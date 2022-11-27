#include "GameViewportScreen.h"

#include <format>

#include <Engine/Core/Application.h>
#include <Engine/ECS/ComponentSystem/ComponentSystemHandler.h>

#include "../../../Engine/Dependencies/ImGui/imgui.h"

namespace Editor
{
	GameViewportScreen::GameViewportScreen(const Engine::ScreenID id) :
		AUIScreen{id, "Game Viewport"},
		m_ViewportSize{512, 512} { }

	GameViewportScreen::~GameViewportScreen() { }

	void GameViewportScreen::DrawImpl()
	{
		using namespace Engine;

		auto gameCameraComponent = Application::GetComponentSystem().GetCameraSystem().GetGameCamera();
		auto& renderTarget = gameCameraComponent->GetRenderTarget();

		if ((m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f) &&
			(m_ViewportSize.x != renderTarget.GetInfo().Width ||
			m_ViewportSize.y != renderTarget.GetInfo().Height))
		{
			m_ViewportSize.x = renderTarget.GetInfo().Width;
			m_ViewportSize.y = renderTarget.GetInfo().Height;
		}
		
		ImGui::Begin(GetNameAndIDLabel());

		auto displaySize = ImGui::GetContentRegionAvail();
		float ratio = (float)displaySize.x / (float)renderTarget.GetInfo().Width;
		if (displaySize.x > renderTarget.GetInfo().Width)
		{
			ratio = (float)displaySize.x / (float)renderTarget.GetInfo().Width;
			m_ViewportSize.x = displaySize.x * ratio;
			m_ViewportSize.y = displaySize.y * ratio;
		}
		else if (displaySize.y > renderTarget.GetInfo().Height)
		{
			ratio = (float)displaySize.y / (float)renderTarget.GetInfo().Height;
			m_ViewportSize.x = displaySize.x * ratio;
			m_ViewportSize.y = displaySize.y * ratio;
		}
		else
		{
			
		}

		if (gameCameraComponent == nullptr)
		{
			ImGui::End();
			return;
		}

		ImGui::Image(&renderTarget.GetFrame(), ImVec2(m_ViewportSize.x, m_ViewportSize.y));
		
		ImGui::End();
	}
}
