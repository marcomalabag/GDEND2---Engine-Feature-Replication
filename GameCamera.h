#pragma once
#include "GameObject/Camera.h"
#include "GameObject/GameObjectManager.h"


class GameCamera: public Camera
{
public:
	GameCamera(String name);
	void update(float deltaTime) override;
	~GameCamera();
};

