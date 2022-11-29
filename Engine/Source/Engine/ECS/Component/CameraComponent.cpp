#include "pch.h"
#include "CameraComponent.h"

#include "TransformComponent.h"

#include "Engine/Core/Application.h"
#include "Engine/Graphics/Renderer.h"

namespace Engine
{
	CameraComponent::CameraComponent(const EntityID& ownerID,
	                                 SharedPtr<TransformComponent> transform,
	                                 uint32_t width,
	                                 uint32_t height) :
		AComponent{ownerID},
		m_Transform{transform}
	{
		m_Up      = Vector3Float(0.0f, 1.0f, 0.0f);
		m_Front   = Vector3Float(0.0f, 0.0f, 1.0f);
		m_WorldUp = m_Up;

		InitRenderTarget(width, height);
	}

	CameraComponent::~CameraComponent() { }

	void CameraComponent::SetSize(const uint32_t width, const uint32_t height)
	{
		const auto* storedFramebuffer = m_RenderTarget.release();
		delete storedFramebuffer;

		InitRenderTarget(width, height);
	}

	void CameraComponent::InitRenderTarget(const uint32_t width, const uint32_t height)
	{
		FramebufferProfile resizedFramebufferProfile;
		resizedFramebufferProfile.Width  = width;
		resizedFramebufferProfile.Height = height;

		m_RenderTarget = Application::GetRenderer().
		                 GetDevice().CreateFramebuffer(resizedFramebufferProfile);
	}

	void CameraComponent::SetPosition(const Vector3Float& position) const
	{
		m_Transform->Position = position;
	}

	void CameraComponent::SetRotation(const Vector3Float& rotation) const
	{
		m_Transform->Rotation = rotation;
	}

	const Vector3Float& CameraComponent::GetPosition() const
	{
		return m_Transform->Position;
	}

	const Vector3Float& CameraComponent::GetRotation() const
	{
		return m_Transform->Rotation;
	}

	Matrix4 CameraComponent::GetViewProjMatrix()
	{
		const float aspectRatio = (float)m_RenderTarget->GetInfo().Width / (float)m_RenderTarget->GetInfo().Height;

		m_ProjMatrix = Matrix4::CreatePerspectiveFieldOfView(DegreesToRadians(FoV),
		                                                     aspectRatio,
		                                                     0.001f, 1000.0f);
		Matrix4 result = m_ViewMatrix * m_ProjMatrix;
		result = result.Transpose();
		return result;
	}

	void CameraComponent::Update()
	{
		UpdateCameraVectors();
		UpdateViewMatrix();
	}

	void CameraComponent::UpdateViewMatrix()
	{
		const float yaw   = DegreesToRadians(m_Transform->Rotation.x);
		const float pitch = DegreesToRadians(m_Transform->Rotation.y);
		const float roll        = DegreesToRadians(m_Transform->Rotation.z);

		const Matrix4 cameraRotationMatrix = Matrix4::CreateFromYawPitchRoll(pitch, yaw, roll);

		Vector3Float target = Vector3Float::Transform(m_Front, cameraRotationMatrix);
		
		target += m_Transform->Position;

		Vector3Float up = Vector3Float::Transform(m_Up, cameraRotationMatrix);

		m_ViewMatrix = Matrix4::CreateLookAt(m_Transform->Position,
		                                     target,
		                                     up);
	}

	void CameraComponent::UpdateCameraVectors()
	{
		// m_Front.x = std::cos(yaw) * std::cos(pitch);
		// m_Front.y = std::sin(pitch);
		// m_Front.z = std::sin(yaw) * std::cos(pitch);
		//
		// m_Front.x = 0;
		// m_Front.y = 0;
		// m_Front.z = m_Transform->Position.z + 11.0f;
		// m_Front.Normalize();
		//
		// m_Right = m_Front.Cross(m_WorldUp);
		// m_Right.Normalize();
		//
		// m_Up = m_Right.Cross(m_Front);
		// m_Up.Normalize();
	}

	Framebuffer& CameraComponent::GetRenderTarget() const
	{
		return *m_RenderTarget;
	}
}
