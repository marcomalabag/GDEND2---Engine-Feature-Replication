#pragma once
#include "Debug.h"
#include "Math/Color.h"
#include "Math/Matrix4x4.h"

#include "AComponent.h"
#include "RenderData.h"

#include "Graphics/VertexShader.h"
#include "Graphics/PixelShader.h"

#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/ConstantBuffer.h"

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

	// Functionality for now, issue when it needs to sort for transparency
	void draw(const Matrix4x4& viewProjMatrix) const;

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
