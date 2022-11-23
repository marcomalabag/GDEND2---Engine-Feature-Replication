#pragma once
#include "Debug.h"

#include "AComponent.h"
#include "RenderData.h"

#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/ConstantBuffer.h"
#include "Graphics/Material.h"

class AGameObject;
class RenderComponent final : public AComponent
{
public:
	RenderComponent(AGameObject& owner,
	                RenderData* renderData,
	                Material* material);
	~RenderComponent() override;

	MAKE_COMPONENT(Render)

	RenderComponent(const RenderComponent&)                = delete;
	RenderComponent& operator=(const RenderComponent&)     = delete;
	RenderComponent(RenderComponent&&) noexcept            = delete;
	RenderComponent& operator=(RenderComponent&&) noexcept = delete;

private:
	RenderData* renderData;
	Material* material;
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;
};
