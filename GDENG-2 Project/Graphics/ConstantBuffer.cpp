#include "ConstantBuffer.h"
#include "Debug.h"
#include "GraphicsEngine.h"

ConstantBuffer::ConstantBuffer(ID3D11Device& device,
                               const void* bufferData,
                               const UINT bufferSize) :
	buffer{nullptr},
	dataTypeSize{bufferSize},
	bufferSize{bufferSize},
	elementCount{1}
{
	D3D11_BUFFER_DESC bufferDesc   = {};
	bufferDesc.ByteWidth           = this->bufferSize;
	bufferDesc.Usage               = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags      = 0;
	bufferDesc.MiscFlags           = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem                = bufferData;

	const HRESULT result = device.CreateBuffer(&bufferDesc,
	                                           &initData,
	                                           &this->buffer);

	Debug::Assert(SUCCEEDED(result),
	              "Failed to create Constant buffer!");
}

ID3D11Buffer* ConstantBuffer::getBuffer() const
{
	return this->buffer;
}

ConstantBuffer::~ConstantBuffer()
{
	if (this->buffer != nullptr)
	{
		this->buffer->Release();
	}
}
