#include "ConstantBuffer.h"
#include "Debug.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

ConstantBuffer::ConstantBuffer(const void* buffer,
                               const UINT sizeBuffer)
{
	D3D11_BUFFER_DESC constantBufferDesc   = {};
	constantBufferDesc.ByteWidth           = sizeBuffer;
	constantBufferDesc.Usage               = D3D11_USAGE_DEFAULT;
	constantBufferDesc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags      = 0;
	constantBufferDesc.MiscFlags           = 0;
	constantBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA constantBufferInitData = {};
	constantBufferInitData.pSysMem                = buffer;

	const HRESULT result = GraphicsEngine::getInstance()->getDevice().CreateBuffer(&constantBufferDesc,
	                                                                               &constantBufferInitData,
	                                                                               &this->buffer);

	Debug::Assert(SUCCEEDED(result), "Failed to create Constant buffer!");
}

void ConstantBuffer::update(const DeviceContext& deviceContext,
                            const void* updatedBufferData) const
{
	deviceContext.deviceContext->UpdateSubresource(this->buffer,
	                                               NULL,
	                                               nullptr,
	                                               updatedBufferData,
	                                               NULL,
	                                               NULL);
}

ConstantBuffer::~ConstantBuffer()
{
	if (this->buffer != nullptr)
	{
		this->buffer->Release();
		delete this;
	}
}
