#include "pch.h"
#include "Cylinder.h"

#include "Engine/ECS/Component/TransformComponent.h"
#include "Engine/ECS/Component/RenderComponent.h"
#include "Engine/ResourceManagement/Shader/ShaderLibrary.h"
#include "Engine/Graphics/Primitives/Primitive.h"
#include "Engine/ResourceManagement/Core/ResourceSystem.h"

namespace Engine{
	Engine::Cylinder::Cylinder(EntityID id,
	StringView name, ComponentRegistry* componentRegistry) :
		Entity{ id, name, componentRegistry }
	{
		RenderData* CylinderRenderData = Primitive::Cylinder(2, 6, 6);
		Application::GetResourceSystem().Load<VertexShader>("Assets/Shaders/Basic/TexturedShader.hlsl");
		Application::GetResourceSystem().Load<PixelShader>("Assets/Shaders/Basic/TexturedShader.hlsl");

		auto transform = AttachComponent<TransformComponent>();

		auto vertexShader = Application::GetResourceSystem().Get<VertexShaderResource>("TexturedShader");
		auto pixelShader = Application::GetResourceSystem().Get<PixelShaderResource>("TexturedShader");

		AttachComponent<RenderComponent>(CylinderRenderData, vertexShader, pixelShader, transform);
	}

	Cylinder::~Cylinder() = default;
};

