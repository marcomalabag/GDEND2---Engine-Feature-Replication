#pragma once
#include "Debug.h"

#include "ECS/Core/AComponent.h"
#include "Graphics/RenderData.h"
#include "TransformComponent.h"

#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/ConstantBuffer.h"
#include "Graphics/VertexShader.h"
#include "Graphics/PixelShader.h"

class AGameObject;
class RenderComponent final : public AComponent
{
public:
	RenderComponent(AGameObject& owner,
	                RenderData* renderData,
	                VertexShader* vertexShaderRef,
	                PixelShader* pixelShaderRef,
	                TransformComponent& transformComponent);
	~RenderComponent() override;

	MAKE_COMPONENT(Render)

	RenderComponent(const RenderComponent&)                = delete;
	RenderComponent& operator=(const RenderComponent&)     = delete;
	RenderComponent(RenderComponent&&) noexcept            = delete;
	RenderComponent& operator=(RenderComponent&&) noexcept = delete;

private:
	RenderData* renderData;
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;
	TransformComponent& transform;
};
