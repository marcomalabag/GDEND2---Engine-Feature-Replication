#include "VertexBuffer.h"

#include "Debug.h"
#include "RenderData.h"

VertexBuffer::VertexBuffer(ID3D11Device& device,
                           const RenderData& renderData,
                           const VertexShader& vertexShader) :
	buffer{nullptr},
	layout{nullptr},
	dataTypeSize{renderData.VertexSize},
	bufferSize{renderData.VertexSize * renderData.VertexCount},
	elementCount{renderData.IndexCount}
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage             = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth         = (UINT)this->bufferSize;
	bufferDesc.BindFlags         = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags    = 0;
	bufferDesc.MiscFlags         = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem                = renderData.Vertices;

	HRESULT result = device.CreateBuffer(&bufferDesc,
	                                     &initData,
	                                     &this->buffer);
	
	Debug::Assert(SUCCEEDED(result),
	              "Failed to create Vertex buffer!");

	result = device.CreateInputLayout(renderData.VertexLayout,
	                                  renderData.VertexLayoutElementCount,
	                                  vertexShader.getByteCodeData(),
	                                  vertexShader.getByteCodeSizeData(),
	                                  &this->layout);

	Debug::Assert(SUCCEEDED(result),
	              "Failed to create Vertex layout!");
}

ID3D11Buffer* VertexBuffer::getBuffer() const
{
	return this->buffer;
}

ID3D11InputLayout* VertexBuffer::getLayout() const
{
	return this->layout;
}

size_t VertexBuffer::getBufferSize() const
{
	return this->bufferSize;
}

unsigned int VertexBuffer::getElementCount() const
{
	return this->elementCount;
}

VertexBuffer::~VertexBuffer()
{
	this->layout->Release();
	this->buffer->Release();
}
