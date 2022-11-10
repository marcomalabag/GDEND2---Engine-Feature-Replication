#include "PixelShader.h"
#include "Debug.h"

PixelShader::PixelShader(ID3DBlob* pixelShaderBlob) :
	data{nullptr}
{
	HRESULT result = GraphicsEngine::getInstance()->
	                 getDevice()->
	                 CreatePixelShader(pixelShaderBlob->GetBufferPointer(),
	                                   pixelShaderBlob->GetBufferSize(),
	                                   nullptr,
	                                   &data);

	Debug::Assert(SUCCEEDED(result),
	              "Failed to create Pixel shader!");
}

PixelShader::~PixelShader()
{
	data->Release();
}
