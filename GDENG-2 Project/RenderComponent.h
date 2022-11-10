#pragma once

#include "AComponent.h"

#include "RenderData.h"

#include "VertexShader.h"
#include "PixelShader.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

class Camera;

class RenderComponent final : public AComponent
{
public:
	RenderComponent(AGameObject& owner,
					RenderData* renderData,
					VertexShader* vertexShader,
					PixelShader* pixelShader);

	~RenderComponent() override;

	void Draw(Camera& camera) const;

	MAKE_COMPONENT(Render)

	RenderComponent(const RenderComponent&) = delete;

	RenderComponent& operator=(const RenderComponent&) = delete;

	RenderComponent(RenderComponent&&) noexcept = delete;

	RenderComponent& operator=(RenderComponent&&) noexcept = delete;

	// Color AlbedoColor = Color(1.0f, 1.0f, 1.0f, 1.0f);

private:
	// Material
	//	Shader
	//		VertexShader
	//		PixelShader
	//	ConstantBuffers
	// Buffers
	//	VertexBuffer
	//	IndexBuffer

	RenderData* m_RenderData;

	VertexShader* m_VertexShader;

	PixelShader* m_PixelShader;

	VertexBuffer* m_VertexBuffer;

	IndexBuffer* m_IndexBuffer;

	ConstantBuffer* m_ConstantBuffer;

	// bool m_HasTexture = false;
	//
	// ID3D11ShaderResourceView* m_TextureView = nullptr;
	//
	// int m_TextureWidth;
	//
	// int m_TextureHeight;
	//
	// ID3D11SamplerState* m_TextureSampler = nullptr;
};
