#include "AUIScreen.h"

AUIScreen::AUIScreen(const UIID& id, std::string_view name) :
	id{id},
	name{name.data()},
	nameIDLabel{std::string(name.data()) + "##" + std::to_string(id)},
	isOpen{true}
{
}


UILabel AUIScreen::getName()
{
	return this->name;
}

AUIScreen::~AUIScreen() = default;

UIID AUIScreen::getID() const
{
	return this->id;
}

const char* AUIScreen::getNameAndIDLabel() const
{
	return this->nameIDLabel.c_str();
}
