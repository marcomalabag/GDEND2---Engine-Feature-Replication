#pragma once
#include "GameObject/AGameObject.h"

#include "Math/Matrix4x4.h"

class Camera : public AGameObject
{
public:
	explicit Camera(std::string_view name);
	~Camera() override;

	virtual void update(float deltaTime);

	Matrix4x4 getViewMatrix();

	void updateViewMatrix();
	
private:
	Matrix4x4 localMatrix;
};
