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
	return localMatrix;
}

// TODO: Finalize calculations
void TransformComponent::recalculateLocalMatrix()
{
	localMatrix = Matrix4x4();
	localMatrix.setIdentity();
}
