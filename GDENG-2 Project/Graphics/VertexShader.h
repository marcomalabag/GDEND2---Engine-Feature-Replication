#pragma once
#include <d3d11.h>

class VertexShader final
{
public:
	explicit VertexShader(ID3D11Device& device,
	                      ID3DBlob* vertexShaderBlob);
	~VertexShader();

	void* getByteCodeData() const;

	unsigned int getByteCodeSizeData() const;

	ID3D11VertexShader* getShader() const;

	VertexShader(const VertexShader&)             = delete;
	VertexShader& operator=(const VertexShader&)  = delete;
	VertexShader(const VertexShader&&)            = delete;
	VertexShader& operator=(const VertexShader&&) = delete;

private:
	ID3DBlob* blob;
	ID3D11VertexShader* data;
};
