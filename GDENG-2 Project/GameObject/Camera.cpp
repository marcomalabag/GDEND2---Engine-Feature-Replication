#include "Camera.h"

#include "Component/TransformComponent.h"

Camera::Camera(const std::string_view name) :
	AGameObject(name)
{
	this->transform().Position = Vector3D(0.0f, 0.0f, -10.0f);
	this->updateViewMatrix();
}

Camera::~Camera()
{
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam;
	Matrix4x4 lookAt;
	worldCam.setIdentity();

	Matrix4x4 temp;
	temp.setIdentity();

	const Vector3D localRot = this->transform().Rotation;

	temp.setRotationX(localRot.x);
	worldCam = worldCam.mulMatrix(temp);

	temp.setRotationY(localRot.y);
	worldCam = worldCam.mulMatrix(temp);

	temp.setTranslation(this->transform().Position);
	worldCam = worldCam.mulMatrix(temp);

	worldCam.getInverse();

	//lookAt = Matrix4x4::lookAt(this->Position, this->Position + this->cameraFront, this->cameraUp);

	this->localMatrix = worldCam;
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->localMatrix;
}


void Camera::update(float deltaTime)
{
	updateViewMatrix();
}
