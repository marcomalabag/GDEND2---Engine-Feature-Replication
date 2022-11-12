#pragma once
#include "AComponent.h"

class TagComponent final : public AComponent
{
public:
	TagComponent(AGameObject& owner,
	             std::string tag);

	~TagComponent() override;

	MAKE_COMPONENT(Tag)

	TagComponent(const TagComponent&) = delete;

	TagComponent& operator=(const TagComponent&) = delete;

	TagComponent(TagComponent&&) noexcept = delete;

	TagComponent& operator=(TagComponent&&) noexcept = delete;

	//TODO: Request for change in the system if tag changes
private:
	std::string tag;
};
