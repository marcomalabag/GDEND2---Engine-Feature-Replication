#pragma once
#include <d3d11.h>
#include <iostream>
#include "GraphicsEngine.h"

class DeviceContext;
class GraphicsEngine;

class PixelShader final
{
public:
	explicit PixelShader(ID3DBlob* pixelShaderBlob);

	~PixelShader();

	[[nodiscard]]
	void* getByteCodeData() const;

	[[nodiscard]]
	unsigned int getByteCodeSizeData() const;

	PixelShader(const PixelShader&) = delete;

	PixelShader& operator=(const PixelShader&) = delete;

	PixelShader(const PixelShader&&) = delete;

	PixelShader& operator=(const PixelShader&&) = delete;

private:
	ID3DBlob* blob;
	ID3D11PixelShader* data;

	friend class GraphicsEngine;
	friend class DeviceContext;
};
