#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "AUIScreen.h"
#include <Window.h>
#include <algorithm>

#include "ViewportScreen.h"

#include "ECS/System/ViewportSystem.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

typedef std::vector<AUIScreen*> UIList;
typedef std::unordered_map<std::string, AUIScreen*> UITable;

class UISystem final
{
public:
	static UISystem* getInstance();
	static void initialize(HWND windowHandle,
	                       UINT windowWidth,
	                       UINT windowHeight);
	static void terminate();

	template <typename UIScreenType, typename... Args>
	UIScreenType* createUI(Args&&... args);

	void destoryUI(AUIScreen* uiScreen);

	void drawAllUI() const;

	void resizeContext(UINT windowWidth, UINT windowHeight);

private:
	UISystem(HWND windowHandle,
	         UINT windowWidth,
	         UINT windowHeight);
	~UISystem();

	static UISystem* instance;
	static ImGuiContext* context;

	UIIDGenerator uiScreenIDGenerator;
	ViewportSystem viewportSystem;

	UIList uiList;
	UITable uiMap;

	UINT windowWidth;
	UINT windowHeight;
};

template <typename UIScreenType, typename... Args>
UIScreenType* UISystem::createUI(Args&&... args)
{
	UIID newID = this->uiScreenIDGenerator.GenerateUIID();
	UIScreenType* newScreen = new UIScreenType(newID, std::forward<Args>(args)...);
	AUIScreen* screen = (AUIScreen*)newScreen;
	this->uiList.push_back(screen);
	this->uiMap[screen->getNameAndIDLabel()] = screen;
	return newScreen;
}

template <>
inline ViewportScreen* UISystem::createUI<ViewportScreen>()
{
	UIID newID = this->uiScreenIDGenerator.GenerateUIID();
	ViewportScreen* newScreen = new ViewportScreen(newID);
	AUIScreen* screen = (AUIScreen*)newScreen;
	this->uiList.push_back(screen);
	this->uiMap[screen->getNameAndIDLabel()] = screen;

	this->viewportSystem.registerViewport(newScreen);
	return newScreen;
}

inline void UISystem::destoryUI(AUIScreen* uiScreen)
{
	if (!this->uiMap.contains(uiScreen->getNameAndIDLabel()))
		return;

	int index = -1;
	for (size_t i = 0; i < this->uiList.size(); i++)
	{
		if (this->uiList[i]->getID() == uiScreen->getID())
		{
			index = (int)i;
		}
	}

	if (index == -1)
		return;

	auto* screenRef = this->uiMap[uiScreen->getNameAndIDLabel()];

	this->uiScreenIDGenerator.AddReservedUIID(screenRef->getID());

	auto screenIndex = std::ranges::remove(this->uiList, screenRef);
	this->uiList.erase(screenIndex.begin(), screenIndex.end());
	this->uiList.shrink_to_fit();

	this->uiMap.erase(uiScreen->getNameAndIDLabel());

	delete screenRef;
}
