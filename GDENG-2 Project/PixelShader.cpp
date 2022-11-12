#include "PixelShader.h"
#include "Debug.h"

PixelShader::PixelShader(ID3DBlob* pixelShaderBlob) :
	blob{std::move(pixelShaderBlob)},
	data{nullptr}
{
	HRESULT result = GraphicsEngine::getInstance()->
	                 getDevice().CreatePixelShader(blob->GetBufferPointer(),
	                                               blob->GetBufferSize(),
	                                               nullptr,
	                                               &data);

	Debug::Assert(SUCCEEDED(result),
	              "Failed to create Pixel shader!");
}

PixelShader::~PixelShader()
{
	data->Release();
}

void* PixelShader::getByteCodeData() const
{
	return blob->GetBufferPointer();
}

unsigned PixelShader::getByteCodeSizeData() const
{
	return blob->GetBufferSize();
}
