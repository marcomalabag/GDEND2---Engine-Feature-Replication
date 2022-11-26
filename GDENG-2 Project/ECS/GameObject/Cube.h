#pragma once
#include "ECS/Core/AGameObject.h"

class Cube final: public AGameObject
{
public:
	explicit Cube(std::string_view name);
	~Cube() override;
};

