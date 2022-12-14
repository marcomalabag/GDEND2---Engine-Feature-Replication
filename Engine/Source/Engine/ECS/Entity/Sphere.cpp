#include "pch.h"
#include "Sphere.h"

#include "Engine/ECS/Component/TransformComponent.h"
#include "Engine/ECS/Component/RenderComponent.h"
#include "Engine/ResourceManagement/Shader/ShaderLibrary.h"
#include "Engine/Graphics/Primitives/Primitive.h"
#include "Engine/ResourceManagement/Core/ResourceSystem.h"

namespace Engine
{
	Sphere::Sphere(const EntityID id, 
		const StringView name, 
		ComponentRegistry* componentRegistry) :
		Entity{ id, name, componentRegistry }
	{
		RenderData* SphereRenderData = Primitive::Sphere(1, 12, 12);
		Application::GetResourceSystem().Load<VertexShader>("Assets/Shaders/Basic/TexturedShader.hlsl");
		Application::GetResourceSystem().Load<PixelShader>("Assets/Shaders/Basic/TexturedShader.hlsl");

		auto transform = AttachComponent<TransformComponent>();

		auto vertexShader = Application::GetResourceSystem().Get<VertexShaderResource>("TexturedShader");
		auto pixelShader = Application::GetResourceSystem().Get<PixelShaderResource>("TexturedShader");

		AttachComponent<RenderComponent>(SphereRenderData, vertexShader, pixelShader, transform);
	}

	Sphere::~Sphere() = default;
}