#pragma once
#include <d3d11.h>

class ConstantBuffer final
{
public:
	ConstantBuffer(ID3D11Device& device,
	               const void* bufferData,
	               UINT bufferSize);
	~ConstantBuffer();

	ID3D11Buffer* getBuffer() const;

	ConstantBuffer(const ConstantBuffer&)             = delete;
	ConstantBuffer& operator=(const ConstantBuffer&)  = delete;
	ConstantBuffer(const ConstantBuffer&&)            = delete;
	ConstantBuffer& operator=(const ConstantBuffer&&) = delete;

private:
	ID3D11Buffer* buffer;
	size_t dataTypeSize;
	size_t bufferSize;
	unsigned int elementCount;
};
