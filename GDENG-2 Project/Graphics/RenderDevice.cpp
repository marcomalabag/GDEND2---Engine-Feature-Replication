﻿#include "RenderDevice.h"

RenderDevice::RenderDevice(ID3D11Device* device) :
	device{device},
	dxgiDevice{nullptr},
	dxgiAdapter{nullptr},
	dxgiFactory{nullptr}
{
	device->QueryInterface(__uuidof(IDXGIDevice),
	                       reinterpret_cast<void**>(&dxgiDevice));

	dxgiDevice->GetParent(__uuidof(IDXGIAdapter),
	                      reinterpret_cast<void**>(&dxgiAdapter));

	dxgiAdapter->GetParent(__uuidof(IDXGIFactory),
	                       reinterpret_cast<void**>(&dxgiFactory));
}

RenderDevice::~RenderDevice()
{
	dxgiAdapter->Release();
	dxgiDevice->Release();
	dxgiFactory->Release();
	device->Release();
}

SwapChain* RenderDevice::CreateSwapChain(const HWND windowHandle,
                                         const unsigned int width,
                                         const unsigned int height) const
{
	return new SwapChain(*device, *dxgiFactory, windowHandle, width, height);
}

VertexBuffer* RenderDevice::CreateVertexBuffer(RenderData& renderData,
                                               VertexShader& vertexShader) const
{
	return new VertexBuffer(*device, renderData, vertexShader);
}

IndexBuffer* RenderDevice::CreateIndexBuffer(RenderData& renderData) const
{
	return new IndexBuffer(*device, renderData);
}

ConstantBuffer* RenderDevice::CreateConstantBuffer(const void* bufferData,
                                                   const size_t bufferSize) const
{
	return new ConstantBuffer(*device, bufferData, bufferSize);
}

VertexShader* RenderDevice::CreateVertexShader(ID3DBlob* vertexShaderBlob) const
{
	return new VertexShader(*device, vertexShaderBlob);
}

PixelShader* RenderDevice::CreatePixelShader(ID3DBlob* pixelShaderBlob) const
{
	return new PixelShader(*device, pixelShaderBlob);
}
