#pragma once
#include <d3d11.h>

class DeviceContext;

class ConstantBuffer final
{
public:
	ConstantBuffer(const void* buffer, UINT sizeBuffer);
	~ConstantBuffer();

	void update(const DeviceContext& deviceContext,
					const void* updatedBufferData) const;

	ID3D11Buffer& getBuffer() const
	{
		return *buffer;
	}

private:
	ID3D11Buffer* buffer = nullptr;

private:
	friend class DeviceContext;
};

