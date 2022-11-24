#pragma once
#include <d3d11.h>
#include <vector>

#include "Math/Color.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

class SwapChain;
class VertexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;
class IndexBuffer;

class RenderContext final
{
public:
	explicit RenderContext(ID3D11DeviceContext* deviceContext);

	~RenderContext();

	void setViewportSize(float width, float height) const;

	void clearRenderTargetView(ID3D11RenderTargetView& renderTarget,
	                           const Color& clearColor) const;

	void clearDepthStencilView(ID3D11DepthStencilView& depthStencil) const;

	void setRenderTarget(ID3D11RenderTargetView* renderTarget,
	                     ID3D11DepthStencilView* depthStencil) const;

	void updateBufferResource(ID3D11Buffer* bufferResource,
	                          const void* updatedBufferData) const;

	void setVertexShader(const VertexShader& vertexShader) const;

	void setPixelShader(const PixelShader& pixelShader) const;

	template <typename Shader>
	void uploadShaderData(ConstantBuffer& dataToUpload);

	void setVertexBuffer(VertexBuffer& vertexBuffer) const;

	void setIndexBuffer(const IndexBuffer& indexBuffer) const;

	void setTopology(const D3D11_PRIMITIVE_TOPOLOGY& topology) const;

	void draw(unsigned int vertexCount,
	          unsigned int startVertexID) const;

	void drawIndexed(unsigned int indexCount,
	                 unsigned int startingIndexID,
	                 int startingVertexID) const;

private:
	ID3D11DeviceContext* deviceContext;

private:
	friend class ConstantBuffer;
};

template <typename Shader>
void RenderContext::uploadShaderData(ConstantBuffer& dataToUpload) {}

template <>
inline void RenderContext::uploadShaderData<VertexShader>(ConstantBuffer& dataToUpload)
{
	const std::vector<ID3D11Buffer*> bufferData
	{
		&dataToUpload.getBuffer()
	};

	this->deviceContext->VSSetConstantBuffers(0,
	                                          1,
	                                          bufferData.data());
}

template <>
inline void RenderContext::uploadShaderData<PixelShader>(ConstantBuffer& dataToUpload)
{
	const std::vector<ID3D11Buffer*> bufferData
	{
		&dataToUpload.getBuffer()
	};

	this->deviceContext->PSSetConstantBuffers(0,
	                                          1,
	                                          bufferData.data());
}
