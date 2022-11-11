#pragma once
#include <string>

#define MAKE_COMPONENT(component)     static const char* getStaticName() { return #component; }               \
									  std::string getName() const override { return #component; }

class AGameObject;
class AComponent
{
public:
	explicit AComponent(AGameObject& owner); 

	virtual ~AComponent();

	[[nodiscard]]
	AGameObject& getOwner() const;

	[[nodiscard]]
	virtual std::string getName() const = 0;

	bool operator==(const AComponent& other) const;

	bool operator!=(const AComponent& other) const;

	AComponent(const AComponent&) = delete;
	
	AComponent& operator=(const AComponent&) = delete;
	
	AComponent(AComponent&&) noexcept = delete;
	
	AComponent& operator=(AComponent&&) noexcept = delete;

protected:
	AGameObject& ownerRef;
};
