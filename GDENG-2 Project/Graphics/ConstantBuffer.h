#pragma once
#include <d3d11.h>

class DeviceContext;

class ConstantBuffer final
{
public:
	ConstantBuffer(ID3D11Device& device, const void* buffer, UINT sizeBuffer);
	~ConstantBuffer();

	void update(const DeviceContext& deviceContext,
					const void* updatedBufferData) const;
	
	ID3D11Buffer& getBuffer() const;

	ConstantBuffer(const ConstantBuffer&)             = delete;
	ConstantBuffer& operator=(const ConstantBuffer&)  = delete;
	ConstantBuffer(const ConstantBuffer&&)            = delete;
	ConstantBuffer& operator=(const ConstantBuffer&&) = delete;
	
private:
	ID3D11Buffer* buffer = nullptr;

private:
	friend class DeviceContext;

	size_t dataTypeSize;
	size_t bufferSize;
	size_t elementCount;
};

