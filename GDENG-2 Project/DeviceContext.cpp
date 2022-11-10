#include "DeviceContext.h"
#include "SwapChain.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext)
{
	this->deviceContext = deviceContext;
}

DeviceContext::~DeviceContext()
{
	this->deviceContext->Release();
}

void DeviceContext::clearRenderTargetColor(SwapChain* swapchain,
                                           float red,
                                           float green,
                                           float blue,
                                           float alpha)
{
	FLOAT clear_color[] = {red, green, blue, alpha};
	this->deviceContext->ClearRenderTargetView(swapchain->RenderTargetView, clear_color);
	this->deviceContext->OMSetRenderTargets(1, &swapchain->RenderTargetView, NULL);
}

void DeviceContext::setViewportSize(const D3D11_VIEWPORT viewport) const
{
	this->deviceContext->RSSetViewports(1, &viewport);
}

void DeviceContext::clearRenderTargetView(ID3D11RenderTargetView& renderTarget,
                                          const Color& clearColor) const
{
	this->deviceContext->ClearRenderTargetView(&renderTarget,
	                                           (const float*)clearColor);
}

void DeviceContext::clearDepthStencilView(ID3D11DepthStencilView& depthStencil) const
{
	this->deviceContext->ClearDepthStencilView(&depthStencil,
	                                           D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
}

void DeviceContext::setRenderTargetTo(ID3D11RenderTargetView* renderTarget,
                                      ID3D11DepthStencilView* depthStencil) const
{
	int numOfRenderTarget = 1;
	if (renderTarget == nullptr)
		numOfRenderTarget = 0;

	this->deviceContext->OMSetRenderTargets(numOfRenderTarget,
	                                        &renderTarget,
	                                        depthStencil);
}
void DeviceContext::updateBufferResource(ID3D11Buffer* bufferResource,
                                         const void* updatedBufferData) const
{
	this->deviceContext->UpdateSubresource(bufferResource,
	                                       NULL,
	                                       nullptr,
	                                       updatedBufferData,
	                                       NULL,
	                                       NULL);
}

void DeviceContext::setVertexShader(const VertexShader& vertexShader) const
{
	this->deviceContext->VSSetShader(vertexShader.data,
	                                 nullptr,
	                                 0);
}

void DeviceContext::setPixelShader(const PixelShader& pixelShader) const
{
	this->deviceContext->PSSetShader(pixelShader.data,
	                                 nullptr,
	                                 0);
}

void DeviceContext::setVertexBuffer(VertexBuffer& vertexBuffer) const
{
	UINT stride = vertexBuffer.getSizeVertexBuffer();
	UINT offset = 0;

	this->deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer.buffer, &stride, &offset);
	this->deviceContext->IASetInputLayout(vertexBuffer.layout);
}

void DeviceContext::setIndexBuffer(const IndexBuffer& indexBuffer) const
{
	this->deviceContext->IASetIndexBuffer(indexBuffer.buffer, DXGI_FORMAT_R32_UINT, 0);
}

void DeviceContext::setTopology(const D3D11_PRIMITIVE_TOPOLOGY& topology) const
{
	this->deviceContext->IASetPrimitiveTopology(topology);
}

void DeviceContext::draw(const unsigned vertexCount,
                         const unsigned startVertexID) const
{
	this->deviceContext->Draw(vertexCount, startVertexID);
}

void DeviceContext::drawIndexed(const unsigned int indexCount,
                                const unsigned int startingIndexID,
                                const int startingVertexID) const
{
	this->deviceContext->DrawIndexed(indexCount,
	                                 startingIndexID,
	                                 startingVertexID);
}

ID3D11DeviceContext* DeviceContext::getContext() const
{
	return this->deviceContext;
}
