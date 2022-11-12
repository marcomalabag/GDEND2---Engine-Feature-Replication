#pragma once
#include <string>

using UILabel = std::string;
class UIManager;

class AUIScreen
{
public:
	explicit AUIScreen(const UILabel& name);
	virtual ~AUIScreen();
	UILabel getName();

	AUIScreen(const AUIScreen&)                = delete;
	AUIScreen& operator=(const AUIScreen&)     = delete;
	AUIScreen(AUIScreen&&) noexcept            = delete;
	AUIScreen& operator=(AUIScreen&&) noexcept = delete;

protected:
	virtual void drawUI() = 0;

	UILabel name;

	friend class UIManager;
};
