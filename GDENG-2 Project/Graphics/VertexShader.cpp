#include "VertexShader.h"
#include "Debug.h"
#include "GraphicsEngine.h"

VertexShader::VertexShader(ID3D11Device& device,
                           ID3DBlob* vertexShaderBlob) :
	blob{std::move(vertexShaderBlob)},
	data{nullptr}
{
	const HRESULT result = device.CreateVertexShader(blob->GetBufferPointer(),
	                                                 blob->GetBufferSize(),
	                                                 nullptr,
	                                                 &this->data);

	Debug::Assert(SUCCEEDED(result),
	              "Failed to create Vertex shader!");
}

VertexShader::~VertexShader()
{
	if (this->data != nullptr)
	{
		this->data->Release();
	}
}

void* VertexShader::getByteCodeData() const
{
	return this->blob->GetBufferPointer();
}

unsigned int VertexShader::getByteCodeSizeData() const
{
	return this->blob->GetBufferSize();
}

ID3D11VertexShader* VertexShader::getShader() const
{
	return this->data;
}
