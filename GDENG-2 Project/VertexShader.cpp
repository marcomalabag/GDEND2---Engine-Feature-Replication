#include "VertexShader.h"
#include "Debug.h"

VertexShader::VertexShader(ID3DBlob* vertexShaderBlob) :
	data{nullptr}
{
	HRESULT result = GraphicsEngine::getInstance()->
	                 getD3Ddevice()->
	                 CreateVertexShader(vertexShaderBlob->GetBufferPointer(),
	                                    vertexShaderBlob->GetBufferSize(),
	                                    nullptr,
	                                    &data);

	Debug::Assert(SUCCEEDED(result),
	              "Failed to create Vertex shader!");
}

VertexShader::~VertexShader()
{
	data->Release();
}
