#pragma once
#include "AGameObject.h"
#include "InputListener.h"
#include "InputSystem.h"
#include "Camera.h"

class CameraMovement : public Camera, public InputListener
{
public:
	CameraMovement(std::string name);
	~CameraMovement();

	void update(float deltaTime) override;

	void defaultmode(float rate, float x, float y, float z);
	void AerialMode(float rate, float x, float y, float z);
	void DownWardMode(float rate, float x, float y, float z);
	void RightViewMode(float rate, float x, float y, float z);
	void LeftViewMode(float rate, float x, float y, float z);

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& deltaMousePos) override;
	virtual void onLeftMouseDown(const Point& mousePosition) override;
	virtual void onLeftMouseUp(const Point& mousePosition) override;
	virtual void onRightMouseDown(const Point& mousePosition) override;
	virtual void onRightMouseUp(const Point& mousePosition) override;
private:
	bool RightMouseDown = false;
	bool defaultBool = true;
	bool AerialBool = false;
	bool RightBool = false;
};

