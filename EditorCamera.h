#pragma once
#include "GameObject/Camera.h"
#include "GameObject/GameObjectManager.h"

class EditorCamera : public Camera
{
public:
	EditorCamera(String name);
	void update(float deltaTime) override;
	~EditorCamera();
};

