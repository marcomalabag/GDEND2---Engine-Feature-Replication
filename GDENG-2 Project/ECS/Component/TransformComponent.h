#pragma once
#include "ECS/Core/AComponent.h"
#include "Math/Matrix4x4.h"

class TransformComponent final : AComponent
{
public:
	Vector3D Position;
	Vector3D Scale;
	Vector3D Rotation;

	explicit TransformComponent(AGameObject& owner);
	~TransformComponent() override;

	MAKE_COMPONENT(Transform)

	Matrix4x4& getLocalMatrix();

	TransformComponent(const TransformComponent&)                = delete;
	TransformComponent& operator=(const TransformComponent&)     = delete;
	TransformComponent(TransformComponent&&) noexcept            = delete;
	TransformComponent& operator=(TransformComponent&&) noexcept = delete;

private:
	void recalculateLocalMatrix();

	Matrix4x4 localMatrix;
};
