#pragma once
#include <d3d11.h>

struct RenderData;
class VertexShader;
class VertexBuffer final
{
public:
	explicit VertexBuffer(ID3D11Device& device,
	                      const RenderData& renderData,
	                      const VertexShader& vertexShader);

	~VertexBuffer();

	ID3D11Buffer* getBuffer() const;

	size_t getBufferSize() const;

	unsigned int getElementCount() const;

	ID3D11InputLayout* getLayout() const;

	VertexBuffer(const VertexBuffer&)             = delete;
	VertexBuffer& operator=(const VertexBuffer&)  = delete;
	VertexBuffer(const VertexBuffer&&)            = delete;
	VertexBuffer& operator=(const VertexBuffer&&) = delete;

private:
	ID3D11Buffer* buffer;
	ID3D11InputLayout* layout;
	size_t dataTypeSize;
	size_t bufferSize;
	unsigned int elementCount;
};
