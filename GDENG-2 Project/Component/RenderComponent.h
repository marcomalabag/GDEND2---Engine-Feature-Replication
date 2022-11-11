#pragma once
#include "Debug.h"
#include "Color.h"
#include "Matrix4x4.h"

#include "AComponent.h"
#include "RenderData.h"

#include "VertexShader.h"
#include "PixelShader.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

class AGameObject;
class RenderComponent final : public AComponent
{
public:
	RenderComponent(AGameObject& owner,
	                RenderData* renderData,
	                VertexShader* vertexShader,
	                PixelShader* pixelShader);

	~RenderComponent() override;

	MAKE_COMPONENT(Render)

	RenderComponent(const RenderComponent&) = delete;

	RenderComponent& operator=(const RenderComponent&) = delete;

	RenderComponent(RenderComponent&&) noexcept = delete;

	RenderComponent& operator=(RenderComponent&&) noexcept = delete;

	Color AlbedoColor = Color(1.0f, 1.0f, 1.0f, 1.0f);

private:
	// Material
	//	Shader
	//		VertexShader
	//		PixelShader
	//	ConstantBuffers
	// Buffers
	//	VertexBuffer
	//	IndexBuffer

	RenderData* renderData;

	VertexShader* vertexShader;

	PixelShader* pixelShader;

	VertexBuffer* vertexBuffer;

	IndexBuffer* indexBuffer;

	ConstantBuffer* constantBuffer;
};
