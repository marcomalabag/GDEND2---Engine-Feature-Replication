#pragma once
#include <d3d11.h>

class GraphicsEngine;
class DeviceContext;

class VertexShader final
{
public:
	explicit VertexShader(ID3D11Device& device, ID3DBlob* vertexShaderBlob);

	~VertexShader();

	[[nodiscard]]
	void* getByteCodeData() const;

	[[nodiscard]]
	unsigned int getByteCodeSizeData() const;

	VertexShader(const VertexShader&)             = delete;
                                                           	VertexShader& operator=(const VertexShader&)  = delete;
                                                           	VertexShader(const VertexShader&&)            = delete;
                                                           	VertexShader& operator=(const VertexShader&&) = delete;

private:
	ID3DBlob* blob;
	ID3D11VertexShader* data;

	friend class GraphicsEngine;

	friend class DeviceContext;
};
