#include "VertexBuffer.h"

#include "Debug.h"
#include "RenderData.h"

VertexBuffer::VertexBuffer(RenderData& renderData,
                           VertexShader& vertexShader) :
	buffer{nullptr},
	layout{nullptr},
	dataTypeSize{renderData.VertexSize},
	bufferSize{renderData.VertexSize * renderData.VertexCount},
	elementCount{renderData.IndexCount}
{
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.Usage             = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth         = bufferSize;
	vertexBufferDesc.BindFlags         = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags    = 0;
	vertexBufferDesc.MiscFlags         = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem                = renderData.Vertices;

	HRESULT result = GraphicsEngine::getInstance()->getDevice().CreateBuffer(&vertexBufferDesc,
	                                                                         &init_data,
	                                                                         &this->buffer);
	Debug::Assert(SUCCEEDED(result), "Failed to create Vertex buffer!");

	result = GraphicsEngine::getInstance()->getDevice().CreateInputLayout(renderData.VertexLayout,
	                                                                      renderData.VertexLayoutElementCount,
	                                                                      vertexShader.getByteCodeData(),
	                                                                      vertexShader.getByteCodeSizeData(),
	                                                                      &this->layout);

	Debug::Assert(SUCCEEDED(result), "Failed to create Vertex layout!");
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
