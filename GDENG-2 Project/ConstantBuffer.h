#pragma once
#include <d3d11.h>
#include "GraphicsEngine.h"
#include "DeviceContext.h"

class DeviceContext;

class ConstantBuffer final
{
public:
	ConstantBuffer(const void* buffer, UINT sizeBuffer);
	~ConstantBuffer();

	void update(const DeviceContext& deviceContext,
					const void* updatedBufferData) const;

private:
	ID3D11Buffer* buffer = nullptr;

private:
	friend class DeviceContext;
};

