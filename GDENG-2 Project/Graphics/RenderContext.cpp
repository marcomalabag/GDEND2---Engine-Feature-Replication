#include "RenderContext.h"

#include <vector>

#include "SwapChain.h"

RenderContext::RenderContext(ID3D11DeviceContext* deviceContext) :
	deviceContext{deviceContext} {}

RenderContext::~RenderContext()
{
	if (this->deviceContext != nullptr)
		this->deviceContext->Release();
}

void RenderContext::setViewportSize(const float width,
                                    const float height) const
{
	D3D11_VIEWPORT viewport = {};
	viewport.Width          = width;
	viewport.Height         = height;
	viewport.MinDepth       = 0.0f;
	viewport.MaxDepth       = 1.0f;
	this->deviceContext->RSSetViewports(1, &viewport);
}

void RenderContext::clearRenderTargetView(ID3D11RenderTargetView& renderTarget,
                                          const Color& clearColor) const
{
	this->deviceContext->ClearRenderTargetView(&renderTarget,
	                                           (const float*)clearColor);
}

void RenderContext::clearDepthStencilView(ID3D11DepthStencilView& depthStencil) const
{
	this->deviceContext->ClearDepthStencilView(&depthStencil,
	                                           D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
}

void RenderContext::setRenderTarget(ID3D11RenderTargetView* renderTarget,
                                    ID3D11DepthStencilView* depthStencil) const
{
	int numOfRenderTarget = 1;
	if (renderTarget == nullptr)
		numOfRenderTarget = 0;

	std::vector<ID3D11RenderTargetView*> renderTargetViews = {};
	renderTargetViews.push_back(renderTarget);

	this->deviceContext->OMSetRenderTargets(numOfRenderTarget,
	                                        renderTargetViews.data(),
	                                        depthStencil);
}
void RenderContext::updateBufferResource(ID3D11Buffer* bufferResource,
                                         const void* updatedBufferData) const
{
	this->deviceContext->UpdateSubresource(bufferResource,
	                                       NULL,
	                                       nullptr,
	                                       updatedBufferData,
	                                       NULL,
	                                       NULL);
}

void RenderContext::setVertexShader(const VertexShader& vertexShader) const
{
	this->deviceContext->VSSetShader(vertexShader.data,
	                                 nullptr,
	                                 0);
}

void RenderContext::setPixelShader(const PixelShader& pixelShader) const
{
	this->deviceContext->PSSetShader(pixelShader.data,
	                                 nullptr,
	                                 0);
}

void RenderContext::setVertexBuffer(VertexBuffer& vertexBuffer) const
{
	UINT stride = vertexBuffer.getBufferSize();
	UINT offset = 0;

	this->deviceContext->IASetVertexBuffers(0,
	                                        1,
	                                        &vertexBuffer.getBuffer(),
	                                        &stride,
	                                        &offset);
	this->deviceContext->IASetInputLayout(vertexBuffer.layout);
}

void RenderContext::setIndexBuffer(const IndexBuffer& indexBuffer) const
{
	this->deviceContext->IASetIndexBuffer(indexBuffer.getBuffer(), DXGI_FORMAT_R32_UINT, 0);
}

void RenderContext::setTopology(const D3D11_PRIMITIVE_TOPOLOGY& topology) const
{
	this->deviceContext->IASetPrimitiveTopology(topology);
}

void RenderContext::draw(const unsigned vertexCount,
                         const unsigned startVertexID) const
{
	this->deviceContext->Draw(vertexCount, startVertexID);
}

void RenderContext::drawIndexed(const unsigned int indexCount,
                                const unsigned int startingIndexID,
                                const int startingVertexID) const
{
	this->deviceContext->DrawIndexed(indexCount,
	                                 startingIndexID,
	                                 0);
}
