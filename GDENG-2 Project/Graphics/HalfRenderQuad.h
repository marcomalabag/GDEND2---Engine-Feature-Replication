#pragma once

#include <d3d11.h>

class IndexBuffer;
class VertexBuffer;
class PixelShader;
class VertexShader;
struct RenderData;

class HalfRenderQuad
{
public:
	explicit HalfRenderQuad();

	~HalfRenderQuad();

	void draw() const;

	HalfRenderQuad(const HalfRenderQuad&) = delete;

	HalfRenderQuad& operator=(const HalfRenderQuad&) = delete;

	HalfRenderQuad(HalfRenderQuad&&) noexcept = delete;

	HalfRenderQuad& operator=(HalfRenderQuad&&) noexcept = delete;
		
private:
	RenderData* renderData;
		
	VertexShader* vertexShader{};
		
	PixelShader* pixelShader{};

	VertexBuffer* vertexBuffer{};

	IndexBuffer* indexBuffer{};
};
