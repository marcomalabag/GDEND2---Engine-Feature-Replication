#pragma once
#include <d3d11.h>

#include "RenderData.h"
#include "VertexShader.h"

class RenderQuad
{
public:
	explicit RenderQuad();

	~RenderQuad();

	void draw(ID3D11ShaderResourceView& frameTexture) const;

	RenderQuad(const RenderQuad&) = delete;

	RenderQuad& operator=(const RenderQuad&) = delete;

	RenderQuad(RenderQuad&&) noexcept = delete;

	RenderQuad& operator=(RenderQuad&&) noexcept = delete;

private:
	RenderData* renderData;

	VertexShader& vertexShader;

	PixelShader& pixelShader;

	VertexBuffer* vertexBuffer;

	IndexBuffer* indexBuffer;

	ID3D11SamplerState* textureSampler;
};
