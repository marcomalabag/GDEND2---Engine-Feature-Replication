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

	// TODO: tbd if private or public (public has consequences)
	std::string Tag;
};
