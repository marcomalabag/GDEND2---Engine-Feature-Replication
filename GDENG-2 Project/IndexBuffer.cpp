#include "IndexBuffer.h"

#include "Debug.h"

IndexBuffer::IndexBuffer(void* list_indices,
                         UINT size_list) :
	sizeList{size_list},
	buffer{nullptr}
{
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage             = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth         = sizeof(UINT) * size_list;
	buff_desc.BindFlags         = D3D11_BIND_INDEX_BUFFER;
	buff_desc.CPUAccessFlags    = 0;
	buff_desc.MiscFlags         = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem                = list_indices;

	HRESULT result = GraphicsEngine::getInstance()->getDevice()->CreateBuffer(&buff_desc,
				   & init_data,
				   &buffer);
	Debug::Assert(SUCCEEDED(result), "Failed to create Index buffer!");
}

UINT IndexBuffer::getSizeIndexList()
{
	return this->sizeList;
}

IndexBuffer::~IndexBuffer()
{
	this->buffer->Release();
}
