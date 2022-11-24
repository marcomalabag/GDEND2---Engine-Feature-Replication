#pragma once
#include <d3d11.h>
#include "SwapChain.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Framebuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"

// Responsible of creating DirectX resources
class RenderDevice
{
public:
	explicit RenderDevice(ID3D11Device* device);
	~RenderDevice();

	SwapChain* createSwapChain(HWND windowHandle, unsigned int width, unsigned int height) const;

	VertexBuffer* createVertexBuffer(RenderData& renderData,
	                                 VertexShader& vertexShader) const;

	IndexBuffer* createIndexBuffer(RenderData& renderData) const;

	ConstantBuffer* createConstantBuffer(const void* bufferData,
	                                     size_t bufferSize) const;

	VertexShader* createVertexShader(ID3DBlob* vertexShaderBlob) const;

	PixelShader* createPixelShader(ID3DBlob* pixelShaderBlob) const;

	// UniquePtr<Texture> CreateTexture(const Texture::Specification& specs) const;

	// UniquePtr<Framebuffer> CreateFramebuffer(const FramebufferProfile& profile) const;

	RenderDevice(const RenderDevice&)                = delete;
	RenderDevice& operator=(const RenderDevice&)     = delete;
	RenderDevice(RenderDevice&&) noexcept            = delete;
	RenderDevice& operator=(RenderDevice&&) noexcept = delete;

private:
	ID3D11Device* device;
	IDXGIDevice* dxgiDevice;
	IDXGIAdapter* dxgiAdapter;
	IDXGIFactory* dxgiFactory;
};
