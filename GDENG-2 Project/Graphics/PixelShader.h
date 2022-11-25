#pragma once
#include <d3d11.h>

class PixelShader final
{
public:
	explicit PixelShader(ID3D11Device& device, ID3DBlob* pixelShaderBlob);

	~PixelShader();

	void* getByteCodeData() const;

	unsigned int getByteCodeSizeData() const;

	ID3D11PixelShader* getShader() const;

	PixelShader(const PixelShader&)             = delete;
	PixelShader& operator=(const PixelShader&)  = delete;
	PixelShader(const PixelShader&&)            = delete;
	PixelShader& operator=(const PixelShader&&) = delete;

private:
	ID3DBlob* blob;
	ID3D11PixelShader* data;
};
