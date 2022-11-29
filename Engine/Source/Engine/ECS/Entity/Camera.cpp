﻿#include "pch.h"
#include "Camera.h"

#include "Engine/ECS/Component/TransformComponent.h"
#include "Engine/ECS/Component/CameraComponent.h"

#include "Engine/ECS/Component/RenderComponent.h"
#include "Engine/ResourceManagement/Shader/ShaderLibrary.h"
#include "Engine/Graphics/Primitives/Primitive.h"
#include "Engine/ResourceManagement/Core/ResourceSystem.h"

#include "Engine/Core/Application.h"

namespace Engine
{
	Camera::Camera(const EntityID id,
	               const StringView name,
	               ComponentRegistry* componentRegistry,
	               uint64_t renderWidth,
	               uint64_t renderHeight) :
		Entity{id, name, componentRegistry}
	{
		auto transform = AttachComponent<TransformComponent>();
		transform->Position.z = 10.0f;
		AttachComponent<CameraComponent>(transform, renderWidth, renderHeight);

		// Application::GetResourceSystem().Load<VertexShader>("Assets/Shaders/Basic/TexturedShader.hlsl");
		// Application::GetResourceSystem().Load<PixelShader>("Assets/Shaders/Basic/TexturedShader.hlsl");
		//
		// auto vertexShader = Application::GetResourceSystem().Get<VertexShaderResource>("TexturedShader");
		// auto pixelShader  = Application::GetResourceSystem().Get<PixelShaderResource>("TexturedShader");
		//
		// RenderData* cubeRenderData = Primitive::Cube();
		//
		// AttachComponent<RenderComponent>(cubeRenderData, vertexShader, pixelShader, transform);
	}

	Camera::~Camera() = default;
	
}

