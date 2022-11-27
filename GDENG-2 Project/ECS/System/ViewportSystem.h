#pragma once
#include <unordered_map>

#include "UI/ViewportScreen.h"

class ViewportSystem final
{
public:
	ViewportSystem();
	~ViewportSystem();

	void registerViewport(ViewportScreen* component);

	void deregisterViewport(UIID viewportHandle);

	ViewportScreen* getViewport(UIID viewportHandle);

	//=====ACTUAL FUNCTIONALITY=====//

private:
	std::vector<ViewportScreen*> viewportScreen;
	std::pmr::unordered_map<UIID, ViewportScreen*> viewportMap;
};
