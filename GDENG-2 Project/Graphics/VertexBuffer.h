#pragma once
#include "GraphicsEngine.h"
#include <d3d11.h>

struct RenderData;
class DeviceContext;

class VertexBuffer final
{
public:
	explicit VertexBuffer(ID3D11Device& device,
	             RenderData& renderData,
	             VertexShader& vertexShader);

	~VertexBuffer();

	[[nodiscard]]
	ID3D11Buffer* getBuffer() const;

	[[nodiscard]]
	ID3D11InputLayout* getLayout() const;

	[[nodiscard]]
	size_t getBufferSize() const;

	[[nodiscard]]
	unsigned int getElementCount() const;

	VertexBuffer(const VertexBuffer&)             = delete;
	VertexBuffer& operator=(const VertexBuffer&)  = delete;
	VertexBuffer(const VertexBuffer&&)            = delete;
	VertexBuffer& operator=(const VertexBuffer&&) = delete;

private:
	ID3D11Buffer* buffer      = nullptr;
	ID3D11InputLayout* layout = nullptr;
	size_t dataTypeSize;
	size_t bufferSize;
	unsigned int elementCount;

	friend class DeviceContext;
};
