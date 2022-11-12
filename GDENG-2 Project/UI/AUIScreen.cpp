#include "AUIScreen.h"

AUIScreen::AUIScreen(const UILabel& name) :
	name{name}
{
}


UILabel AUIScreen::getName()
{
	return this->name;
}

AUIScreen::~AUIScreen() = default;
