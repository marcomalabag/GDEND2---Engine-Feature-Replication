#pragma once
#include <d3d11.h>

#include "Color.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

class SwapChain;
class VertexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;
class IndexBuffer;

class DeviceContext final
{
public:
	explicit DeviceContext(ID3D11DeviceContext* deviceContext);

	~DeviceContext();

	void clearRenderTargetColor(SwapChain* swapchain,
	                            float red,
	                            float green,
	                            float blue,
	                            float alpha);

	// Rendering pipeline
	// Render Begin
	void setViewportSize(D3D11_VIEWPORT viewport) const;

	void clearRenderTargetView(ID3D11RenderTargetView& renderTarget,
	                           const Color& clearColor) const;

	void clearDepthStencilView(ID3D11DepthStencilView& depthStencil) const;

	void setRenderTargetTo(ID3D11RenderTargetView* renderTarget,
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
	// Render End (Unbind render targets)

	ID3D11DeviceContext* getContext() const;

private:
	ID3D11DeviceContext* deviceContext;

private:
	friend class ConstantBuffer;
};

template <typename Shader>
void DeviceContext::uploadShaderData(ConstantBuffer& dataToUpload)
{
}

template <>
inline void DeviceContext::uploadShaderData<VertexShader>(ConstantBuffer& dataToUpload)
{
	this->deviceContext->VSSetConstantBuffers(0,
	                                          1,
	                                          &dataToUpload.buffer);
}

template <>
inline void DeviceContext::uploadShaderData<PixelShader>(ConstantBuffer& dataToUpload)
{
	this->deviceContext->PSSetConstantBuffers(0,
	                                          1,
	                                          &dataToUpload.buffer);
}
