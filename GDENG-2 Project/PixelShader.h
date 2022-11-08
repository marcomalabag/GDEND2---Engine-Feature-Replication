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

private:
	ID3D11PixelShader* data;

private:
	friend class GraphicsEngine;
	friend class DeviceContext;
};

