#include "IndexBuffer.h"
#include "Debug.h"
#include "DeviceContext.h"

IndexBuffer::IndexBuffer(ID3D11Device& device, RenderData& renderData) :
	buffer{nullptr},
	dataTypeSize{sizeof(unsigned int)},
	bufferSize{renderData.IndexCount * sizeof(unsigned int)},
	elementCount{renderData.IndexCount}
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage             = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth         = bufferSize;
	bufferDesc.BindFlags         = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags    = 0;
	bufferDesc.MiscFlags         = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem                = renderData.Indices;

	HRESULT result = device.CreateBuffer(&bufferDesc,
	                                     &initData,
	                                     &buffer);
	
	Debug::Assert(SUCCEEDED(result),
	              "Failed to create Index buffer!");
}

IndexBuffer::~IndexBuffer()
{
	buffer->Release();
}

ID3D11Buffer* IndexBuffer::getBuffer() const
{
	return this->buffer;
}

size_t IndexBuffer::getBufferSize() const
{
	return this->bufferSize;
}

unsigned IndexBuffer::getElementCount() const
{
	return this->elementCount;
}
