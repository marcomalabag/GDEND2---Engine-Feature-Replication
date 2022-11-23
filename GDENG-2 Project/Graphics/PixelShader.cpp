#include "PixelShader.h"
#include "Debug.h"

PixelShader::PixelShader(ID3D11Device& device, ID3DBlob* pixelShaderBlob) :
	blob{std::move(pixelShaderBlob)},
	data{nullptr}
{
	HRESULT result = device.CreatePixelShader(blob->GetBufferPointer(),
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