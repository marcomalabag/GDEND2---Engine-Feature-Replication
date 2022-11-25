#include "PixelShader.h"
#include "Debug.h"

PixelShader::PixelShader(ID3D11Device& device,
                         ID3DBlob* pixelShaderBlob) :
	blob{std::move(pixelShaderBlob)},
	data{nullptr}
{
	const HRESULT result = device.CreatePixelShader(blob->GetBufferPointer(),
	                                                blob->GetBufferSize(),
	                                                nullptr,
	                                                &this->data);

	Debug::Assert(SUCCEEDED(result),
	              "Failed to create Pixel shader!");
}

PixelShader::~PixelShader()
{
	if (this->data != nullptr)
	{
		this->data->Release();
	}
}

void* PixelShader::getByteCodeData() const
{
	return blob->GetBufferPointer();
}

unsigned PixelShader::getByteCodeSizeData() const
{
	return blob->GetBufferSize();
}

ID3D11PixelShader* PixelShader::getShader() const
{
	return this->data;
}
