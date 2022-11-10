#pragma once
#include <d3d11.h>
#include "RenderData.h"

class DeviceContext;

class IndexBuffer final
{
public:
	IndexBuffer(RenderData& renderData);

	~IndexBuffer();

	[[nodiscard]]
	ID3D11Buffer* getBuffer() const;

	[[nodiscard]]
	size_t getBufferSize() const;

	[[nodiscard]]
	unsigned int getElementCount() const;

private:
	ID3D11Buffer* buffer = nullptr;

	size_t dataTypeSize;

	size_t bufferSize;

	unsigned int elementCount;

	friend class DeviceContext;
};
