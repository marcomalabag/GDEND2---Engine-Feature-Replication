#include "ConstantBuffer.h"
#include "Debug.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

ConstantBuffer::ConstantBuffer(ID3D11Device& device,
                               const void* buffer,
                               const UINT sizeBuffer) :
	buffer{nullptr},
	dataTypeSize{sizeBuffer},
	bufferSize{sizeBuffer},
	elementCount{1}
{
	D3D11_BUFFER_DESC bufferDec   = {};
	bufferDec.ByteWidth           = sizeBuffer;
	bufferDec.Usage               = D3D11_USAGE_DEFAULT;
	bufferDec.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
	bufferDec.CPUAccessFlags      = 0;
	bufferDec.MiscFlags           = 0;
	bufferDec.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem                = buffer;

	const HRESULT result = device.CreateBuffer(&bufferDec,
	                                           &initData,
	                                           &this->buffer);

	Debug::Assert(SUCCEEDED(result),
	              "Failed to create Constant buffer!");
}

// void ConstantBuffer::update(const DeviceContext& deviceContext,
//                             const void* updatedBufferData) const
// {
// 	deviceContext.deviceContext->UpdateSubresource(this->buffer,
// 	                                               NULL,
// 	                                               nullptr,
// 	                                               updatedBufferData,
// 	                                               NULL,
// 	                                               NULL);
// }

ID3D11Buffer* ConstantBuffer::getBuffer() const
{
	return buffer;
}

ConstantBuffer::~ConstantBuffer()
{
	if (this->buffer != nullptr)
	{
		this->buffer->Release();
	}
}
