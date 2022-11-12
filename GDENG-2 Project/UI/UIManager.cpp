#include "UIManager.h"
#include <iostream>

#include "EditorViewportScreen.h"
#include "GameViewportScreen.h"

UIManager* UIManager::sharedInstance = NULL;

UIManager::UIManager(HWND windowHandle)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(&GraphicsEngine::getInstance()->getDevice(),
	                    GraphicsEngine::getInstance()->getDeviceContext().getContext());

	UINames uiNames;
	ProfilerScreen* profilerScreen         = new ProfilerScreen();
	this->uiTable[uiNames.PROFILER_SCREEN] = profilerScreen;
	this->uiList.push_back(profilerScreen);

	MenuScreen* menuScreen             = new MenuScreen();
	this->uiTable[uiNames.MENU_SCREEN] = menuScreen;
	this->uiList.push_back(menuScreen);

	InspectorScreen* inspectorScreen        = new InspectorScreen();
	this->uiTable[uiNames.INSPECTOR_SCREEN] = inspectorScreen;
	this->uiList.push_back(inspectorScreen);

	HierarchyScreen* hierarchyScreen        = new HierarchyScreen();
	this->uiTable[uiNames.HIERARCHY_SCREEN] = hierarchyScreen;
	this->uiList.push_back(hierarchyScreen);

	CreditsScreen* creditsScreen          = new CreditsScreen();
	this->uiTable[uiNames.CREDITS_SCREEN] = creditsScreen;
	this->uiList.push_back(creditsScreen);

	EditorViewportScreen* editorViewportScreen = new EditorViewportScreen();
	this->uiTable["EditorViewportScreen"]      = editorViewportScreen;
	this->uiList.push_back(editorViewportScreen);

	GameViewportScreen* gameViewportScreen = new GameViewportScreen();
	this->uiTable["GameViewportScreen"]    = gameViewportScreen;
	this->uiList.push_back(gameViewportScreen);
}

void UIManager::initialize(HWND windowHandle)
{
	sharedInstance = new UIManager(windowHandle);
}

void UIManager::destroy()
{
	delete sharedInstance;
}

void UIManager::drawAllUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::DockSpaceOverViewport();
	UINames uiNames;

	for (int i = 0; i < uiList.size(); i++)
	{
		if (this->uiList[i]->getName() == "Credits Screen" && !showCredits)
		{
			continue;
		}
		else
		{
			this->uiList[i]->drawUI();
		}
	}

	//ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::hideCreditsScreen()
{
	showCredits = false;
}

void UIManager::showCreditsScreen()
{
	showCredits = true;
}

UIManager* UIManager::getInstance()
{
	return sharedInstance;
}

UIManager::~UIManager()
{
}
