#include "CameraMovement.h"
#include <iostream>

CameraMovement::CameraMovement(string name):Camera(name)
{
	InputSystem::getInstance()->addListener(this);
}

CameraMovement::~CameraMovement()
{
	InputSystem::getInstance()->removeListener(this);
}

void CameraMovement::defaultmode(float rate, float x, float y, float z)
{
	if (InputSystem::getInstance()->isKeyDown('W')) {
		z += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		z -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) {
		x -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		x += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void CameraMovement::AerialMode(float rate, float x, float y, float z)
{
	if (InputSystem::getInstance()->isKeyDown('W')) {
		y += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		y -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) {
		x -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		x += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void CameraMovement::DownWardMode(float rate, float x, float y, float z)
{
	if (InputSystem::getInstance()->isKeyDown('W')) {
		y -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		y += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) {
		x -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		x += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void CameraMovement::RightViewMode(float rate, float x, float y, float z)
{
	if (InputSystem::getInstance()->isKeyDown('W')) {
		x += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		x -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) {
		z += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		z -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void CameraMovement::LeftViewMode(float rate, float x, float y, float z)
{
	if (InputSystem::getInstance()->isKeyDown('W')) {
		x -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		x += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) {
		z -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		z += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void CameraMovement::update(float deltaTime)
{
	Vector3D localPos = this->getLocalPosition();
	float x = localPos.x;
	float y = localPos.y;
	float z = localPos.z;
	float moveSpeed = 10.0f;

	if (defaultBool) {

		this->defaultmode(deltaTime * moveSpeed, x, y, z);
	}

	if (this->getLocalRotation().y >= 0.07f) {
		defaultBool = false;
		this->RightViewMode(deltaTime * moveSpeed, x, y, z);
	}

	else if (this->getLocalRotation().y <= -0.07f) {
		defaultBool = false;
		this->LeftViewMode(deltaTime * moveSpeed, x, y, z);
	}

	else {

		defaultBool = true;
	}

	if (this->getLocalRotation().x <= -0.05f) {
		defaultBool = false;
		this->AerialMode(deltaTime * moveSpeed, x, y, z);
	}

	else {
		defaultBool = true;
	}



}

void CameraMovement::onKeyDown(int key)
{
	/*if (key == 'U') {
		std::cout << "default mode is set";
		defaultBool = true;
		AerialBool = false;
		RightBool = false;
	}
	else if (key == 'I') {
		std::cout << "Aerial mode is set";
		defaultBool = false;
		AerialBool = true;
		RightBool = false;
	}
	else if (key == 'O') {
		std::cout << "Right view mode is set";
		defaultBool = false;
		AerialBool = false;
		RightBool = true;
	}*/
}

void CameraMovement::onKeyUp(int key)
{
}

void CameraMovement::onMouseMove(const Point& deltaMousePos)
{
	if (this->RightMouseDown)
	{
		Vector3D localRotation = this->getLocalRotation();
		float x = localRotation.x;
		float y = localRotation.y;
		float z = localRotation.z;

		float speed = 0.005f;
		x += deltaMousePos.y * speed;
		y += deltaMousePos.x * speed;
		std::cout << "X:" << x << "\n";
		std::cout << "Y:" << y << "\n";


		this->setRotation(x, y, z);


		this->updateViewMatrix();
	}


}

void CameraMovement::onLeftMouseDown(const Point& mousePosition)
{
}

void CameraMovement::onLeftMouseUp(const Point& mousePosition)
{
}

void CameraMovement::onRightMouseDown(const Point& mousePosition)
{
	this->RightMouseDown = true;
}

void CameraMovement::onRightMouseUp(const Point& mousePosition)
{
	this->RightMouseDown = false;
}
