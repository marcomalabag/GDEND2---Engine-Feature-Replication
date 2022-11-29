﻿#include "pch.h"
#include "EditorCameraComponent.h"

#include "TransformComponent.h"

#include "Engine/Core/Application.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Input/Input.h"

namespace Engine
{
	EditorCameraComponent::EditorCameraComponent(const EntityID& ownerID,
	                                             SharedPtr<TransformComponent> transform,
	                                             uint64_t width,
	                                             uint64_t height) :
		AComponent{ownerID},
		m_Transform{transform}
	{
		m_Up      = Vector3Float(0.0f, 1.0f, 0.0f);
		m_Front   = Vector3Float(0.0f, 0.0f, 0.0f);
		m_WorldUp = m_Up;

		InitRenderTarget(width, height);
	}

	EditorCameraComponent::~EditorCameraComponent() { }

	void EditorCameraComponent::SetSize(uint64_t width, uint64_t height)
	{
		const auto* storedFramebuffer = m_RenderTarget.release();
		delete storedFramebuffer;

		InitRenderTarget(width, height);
	}

	Matrix4 EditorCameraComponent::GetViewProjMatrix()
	{
		const float aspectRatio = (float)m_RenderTarget->GetInfo().Width / (float)m_RenderTarget->GetInfo().Height;

		m_ProjMatrix = Matrix4::CreatePerspectiveFieldOfView(DegreesToRadians(FoV),
		                                                     aspectRatio,
		                                                     0.001f, 1000.0f);
		m_ProjMatrix = m_ProjMatrix.Transpose();

		return m_ProjMatrix * m_ViewMatrix;
	}

	void EditorCameraComponent::Update()
	{
		UpdateCameraVectors();

		if (m_IsFocused)
		{
			const KeyboardInput keyInput = Input::Keyboard();
			if (keyInput.KeyState == KeyState::KeyDown)
			{
				if (keyInput.KeyCode == KeyCode::Q)
				{
					m_Transform->Position.z -= 50.0f * Application::GetInfo().Time.DeltaTimeSec;
				}

				if (keyInput.KeyCode == KeyCode::E)
				{
					m_Transform->Position.z += 50.0f * Application::GetInfo().Time.DeltaTimeSec;
				}

				if (keyInput.KeyCode == KeyCode::A)
				{
					m_Transform->Position.x += 50.0f * Application::GetInfo().Time.DeltaTimeSec;
				}

				if (keyInput.KeyCode == KeyCode::D)
				{
					m_Transform->Position.x -= 50.0f * Application::GetInfo().Time.DeltaTimeSec;
				}

				if (keyInput.KeyCode == KeyCode::W)
				{
					m_Transform->Position.y += 50.0f * Application::GetInfo().Time.DeltaTimeSec;
				}

				if (keyInput.KeyCode == KeyCode::S)
				{
					m_Transform->Position.y -= 50.0f * Application::GetInfo().Time.DeltaTimeSec;
				}

				// Rotation
				if (keyInput.KeyCode == KeyCode::J)
				{
					m_Transform->Rotation.y += 50.0f * Application::GetInfo().Time.DeltaTimeSec;
				}

				if (keyInput.KeyCode == KeyCode::L)
				{
					m_Transform->Rotation.y -= 50.0f * Application::GetInfo().Time.DeltaTimeSec;
				}

				if (keyInput.KeyCode == KeyCode::K)
				{
					m_Transform->Rotation.x -= 50.0f * Application::GetInfo().Time.DeltaTimeSec;
				}

				if (keyInput.KeyCode == KeyCode::I)
				{
					m_Transform->Rotation.x += 50.0f * Application::GetInfo().Time.DeltaTimeSec;
				}
			}
		}
		
		UpdateViewMatrix();
	}

	void EditorCameraComponent::SetPosition(const Vector3Float& position) const
	{
		m_Transform->Position = position;
	}

	void EditorCameraComponent::SetRotation(const Vector3Float& rotation) const
	{
		m_Transform->Rotation = rotation;
	}
	
	void EditorCameraComponent::SetFocus(bool flag)
	{
		m_IsFocused = flag;	
	}

	const Vector3Float& EditorCameraComponent::GetPosition() const
	{
		return m_Transform->Position;
	}

	const Vector3Float& EditorCameraComponent::GetRotation() const
	{
		return m_Transform->Rotation;
	}

	Framebuffer& EditorCameraComponent::GetRenderTarget() const
	{
		return *m_RenderTarget;
	}

	void EditorCameraComponent::InitRenderTarget(uint64_t width, uint64_t height)
	{
		FramebufferProfile resizedFramebufferProfile;
		resizedFramebufferProfile.Width = width;
		resizedFramebufferProfile.Height = height;
		m_RenderTarget = Application::GetRenderer().GetDevice().CreateFramebuffer(resizedFramebufferProfile);
	}

	void EditorCameraComponent::UpdateViewMatrix()
	{
		m_ViewMatrix = m_Transform->GetLocalMatrix();
	}

	void EditorCameraComponent::UpdateCameraVectors()
	{
		float pitch = m_Transform->Rotation.x;
		float yaw   = m_Transform->Rotation.y;
		float roll  = m_Transform->Rotation.z;

		m_Front.x = std::cos(DegreesToRadians(yaw)) * std::cos(DegreesToRadians(pitch));
		m_Front.y = std::sin(DegreesToRadians(pitch));
		m_Front.z = std::sin(DegreesToRadians(yaw)) * std::cos(DegreesToRadians(pitch));
		m_Front.Normalize();

		m_Right = m_Front.Cross(m_WorldUp);
		m_Right.Normalize();

		m_Up = m_Right.Cross(m_Front);
		m_Up.Normalize();
	}
}