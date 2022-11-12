#pragma once
#include <d3d11.h>

class IndexBuffer;
class VertexBuffer;
class PixelShader;
class VertexShader;
struct RenderData;

class RenderQuad
{
public:
	explicit RenderQuad();

	~RenderQuad();

	void draw(ID3D11ShaderResourceView& renderTargetFrame) const;

	RenderQuad(const RenderQuad&) = delete;

	RenderQuad& operator=(const RenderQuad&) = delete;

	RenderQuad(RenderQuad&&) noexcept = delete;

	RenderQuad& operator=(RenderQuad&&) noexcept = delete;
		
private:
	RenderData* renderData;
		
	VertexShader* vertexShader{};
		
	PixelShader* pixelShader{};

	VertexBuffer* vertexBuffer{};

	IndexBuffer* indexBuffer{};

	ID3D11SamplerState* textureSampler;
};
