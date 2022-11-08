#pragma once
#include "GraphicsEngine.h"
#include <d3d11.h>

class GraphicsEngine;
class DeviceContext;

class VertexShader final
{
public:
	explicit VertexShader(ID3DBlob* vertexShaderBlob);
	
	~VertexShader();

	VertexShader(const VertexShader&) = delete;

	VertexShader& operator=(const VertexShader&) = delete;

	VertexShader(const VertexShader&&) = delete;

	VertexShader& operator=(const VertexShader&&) = delete;

private:
	ID3D11VertexShader* data;

private:
	friend class GraphicsEngine;
	
	friend class DeviceContext;

};

