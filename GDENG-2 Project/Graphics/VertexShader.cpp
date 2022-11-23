#include "VertexShader.h"
#include "Debug.h"
#include "GraphicsEngine.h"

VertexShader::VertexShader(ID3D11Device& device, ID3DBlob* vertexShaderBlob) :
	blob{std::move(vertexShaderBlob)},
	data{nullptr}
{
	const HRESULT result = device.CreateVertexShader(blob->GetBufferPointer(),
	                                                 blob->GetBufferSize(),
	                                                 nullptr,
	                                                 &data);

	Debug::Assert(SUCCEEDED(result),
	              "Failed to create Vertex shader!");
}

VertexShader::~VertexShader()
{
	data->Release();
}

void* VertexShader::getByteCodeData() const
{
	return blob->GetBufferPointer();
}

unsigned int VertexShader::getByteCodeSizeData() const
{
	return blob->GetBufferSize();
}
