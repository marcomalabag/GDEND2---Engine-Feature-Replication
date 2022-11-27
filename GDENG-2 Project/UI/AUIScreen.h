#pragma once
#include <string>
#include "UIIDGenerator.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

using UILabel = std::string;
class UIManager;

class AUIScreen
{
public:
	explicit AUIScreen(const UIID& id, std::string_view name);
	virtual ~AUIScreen();

	UIID getID() const;

	[[nodiscard]]
	const char* getNameAndIDLabel() const;
	
	UILabel getName();

	AUIScreen(const AUIScreen&)                = delete;
	AUIScreen& operator=(const AUIScreen&)     = delete;
	AUIScreen(AUIScreen&&) noexcept            = delete;
	AUIScreen& operator=(AUIScreen&&) noexcept = delete;

protected:
	virtual void drawUI() = 0;

	UIID id;
	std::string name;
	std::string nameIDLabel;
	bool isOpen = false;

	friend class UISystem;
};
