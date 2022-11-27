#pragma once
#include "GameObject/Camera.h"
#include "GameObject/GameObjectManager.h"
#include "GameObject/AGameObject.h"
#include "GameObject/CameraMovement.h"
#include "CameraRenderComponent.h"

class EditorCamera : public Camera
{
public:
	EditorCamera(String name);
	void update(float deltaTime) override;
	~EditorCamera();
};

