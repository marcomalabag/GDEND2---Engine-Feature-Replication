#include "TransformComponent.h"

TransformComponent::TransformComponent(AGameObject& owner) :
		AComponent{owner},
		Position{Vector3D{0.0f, 0.0f, 0.0f}},
		Scale{Vector3D{1.0f, 1.0f, 1.0f}},
		Rotation{Vector3D{0.0f, 0.0f, 0.0f}}
{
}

TransformComponent::~TransformComponent() = default;

Matrix4x4& TransformComponent::getLocalMatrix()
{
	recalculateLocalMatrix();
	return this->localMatrix;
}

void TransformComponent::recalculateLocalMatrix()
{
	this->localMatrix = Matrix4x4();

	Matrix4x4 translate;
	Matrix4x4 scale;
	Matrix4x4 rotateZ;
	Matrix4x4 rotateF;
	Matrix4x4 rotateGl;
	Matrix4x4 rotateTotal;
	
	this->localMatrix.setIdentity();
	
	translate.setIdentity();
	scale.setIdentity();

	translate.setTranslation(this->Position);
	scale.setScale(this->Scale);
	const Vector3D rotation = Vector3D(this->Rotation);

	rotateZ.setIdentity();
	rotateZ.setRotationZ(rotation.z);

	rotateF.setIdentity();
	rotateF.setRotationX(rotation.x);

	rotateGl.setIdentity();
	rotateGl.setRotationY(rotation.y);

	rotateTotal.setIdentity();
	rotateTotal = rotateTotal.mulMatrix(rotateF.mulMatrix(rotateGl.mulMatrix(rotateZ)));
	this->localMatrix = this->localMatrix.mulMatrix(scale.mulMatrix(rotateTotal));
	this->localMatrix = this->localMatrix.mulMatrix(translate);
}
