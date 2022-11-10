#include "VertexBuffer.h"

#include "Debug.h"

VertexBuffer::VertexBuffer(void* list_vertices,
                           UINT size_vertex,
                           UINT size_list,
                           void* shader_byte_code,
                           size_t size_byte_shader) :
	buffer{nullptr},
	layout{nullptr}
{
	D3D11_BUFFER_DESC vertex_buffer_desc = {};
	vertex_buffer_desc.Usage             = D3D11_USAGE_DEFAULT;
	vertex_buffer_desc.ByteWidth         = size_vertex * size_list;
	vertex_buffer_desc.BindFlags         = D3D11_BIND_VERTEX_BUFFER;
	vertex_buffer_desc.CPUAccessFlags    = 0;
	vertex_buffer_desc.MiscFlags         = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem                = list_vertices;

	this->sizeVertexBuffer = size_vertex;
	this->sizeVertexList   = size_list;

	HRESULT result = GraphicsEngine::getInstance()->getDevice()->CreateBuffer(&vertex_buffer_desc,
	                                                                             &init_data,
	                                                                             &this->buffer);
	Debug::Assert(SUCCEEDED(result), "Failed to create Vertex buffer!");

	D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[3] {
		{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		{
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			12,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		{
			"COLOR",
			1,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			24,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		}
	};

	UINT size_layout = 3ULL;

	result = GraphicsEngine::getInstance()->getDevice()->CreateInputLayout(layout, size_layout,
				   shader_byte_code, size_byte_shader, &this->layout);
	
	Debug::Assert(SUCCEEDED(result), "Failed to create Vertex layout!");
}

ID3D11Buffer* VertexBuffer::getBuffer()
{
	return this->buffer;
}

ID3D11InputLayout* VertexBuffer::getLayout()
{
	return this->layout;
}

UINT VertexBuffer::getSizeVertexBuffer()
{
	return this->sizeVertexBuffer;
}

UINT VertexBuffer::getSizeVertexList()
{
	return this->sizeVertexList;
}

VertexBuffer::~VertexBuffer()
{
	this->layout->Release();
	this->buffer->Release();
}
