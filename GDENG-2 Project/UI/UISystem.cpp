#include "UISystem.h"

#include "Graphics/GraphicsEngine.h"

UISystem* UISystem::instance = nullptr;

ImGuiContext* UISystem::context = nullptr;

UISystem::UISystem(const HWND windowHandle,
                   const UINT windowWidth,
                   const UINT windowHeight) :
	windowWidth{windowWidth},
	windowHeight{windowHeight}
{
	IMGUI_CHECKVERSION();
	context = ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;
	ImGui::SetCurrentContext(context);

	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding              = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}


	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(GraphicsEngine::getInstance()->getDevice().device,
	                    GraphicsEngine::getInstance()->getDeviceContext().deviceContext);
}

UISystem::~UISystem()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

UISystem* UISystem::getInstance()
{
	return instance;
}

void UISystem::initialize(HWND windowHandle,
                          UINT windowWidth,
                          UINT windowHeight)
{
	if (instance == nullptr)
	{
		instance = new UISystem(windowHandle, windowWidth, windowHeight);
	}
}

void UISystem::terminate()
{
	delete instance;
}

void UISystem::drawAllUI() const
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::DockSpaceOverViewport();

	static bool showDemo = true;
	ImGui::ShowDemoWindow(&showDemo);

	for (auto i = 0ULL; i < this->uiList.size(); ++i)
	{
		this->uiList[i]->drawUI();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();

	io.DisplaySize = ImVec2((float)this->windowWidth,
	                        (float)this->windowHeight);

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}
void UISystem::resizeContext(const UINT windowWidth,
                             const UINT windowHeight)
{
	this->windowWidth  = windowWidth;
	this->windowHeight = windowHeight;

	ImGuiIO& io    = ImGui::GetIO();
	io.DisplaySize = ImVec2((float)this->windowWidth,
	                        (float)this->windowHeight);
}
