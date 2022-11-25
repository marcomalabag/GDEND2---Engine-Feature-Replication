#include "IndexBuffer.h"
#include "Debug.h"

IndexBuffer::IndexBuffer(ID3D11Device& device,
                         const RenderData& renderData) :
	buffer{nullptr},
	dataTypeSize{sizeof(unsigned int)},
	bufferSize{renderData.IndexCount * sizeof(unsigned int)},
	elementCount{renderData.IndexCount}
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage             = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth         = (UINT)this->bufferSize;
	bufferDesc.BindFlags         = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags    = 0;
	bufferDesc.MiscFlags         = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem                = renderData.Indices;

	const HRESULT result = device.CreateBuffer(&bufferDesc,
	                                           &initData,
	                                           &this->buffer);

	Debug::Assert(SUCCEEDED(result),
	              "Failed to create Index buffer!");
}

IndexBuffer::~IndexBuffer()
{
	if (buffer != nullptr)
	{
		buffer->Release();
	}
}

ID3D11Buffer* IndexBuffer::getBuffer() const
{
	return this->buffer;
}

size_t IndexBuffer::getBufferSize() const
{
	return this->bufferSize;
}

unsigned int IndexBuffer::getElementCount() const
{
	return this->elementCount;
}
