#pragma once
#include <d3d11.h>
#include "RenderData.h"

class DeviceContext;

class IndexBuffer final
{
public:
	explicit IndexBuffer(ID3D11Device& device, RenderData& renderData);

	~IndexBuffer();

	[[nodiscard]]
	ID3D11Buffer* getBuffer() const;

	[[nodiscard]]
	size_t getBufferSize() const;

	[[nodiscard]]
	unsigned int getElementCount() const;

	IndexBuffer(const IndexBuffer&)                = delete;
	IndexBuffer& operator=(const IndexBuffer&)     = delete;
	IndexBuffer(IndexBuffer&&) noexcept            = delete;
	IndexBuffer& operator=(IndexBuffer&&) noexcept = delete;
	
private:
	ID3D11Buffer* buffer = nullptr;
	size_t dataTypeSize;
	size_t bufferSize;
	size_t elementCount;

	friend class DeviceContext;
};
