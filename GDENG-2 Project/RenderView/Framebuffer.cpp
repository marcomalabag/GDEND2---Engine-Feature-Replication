#include "Framebuffer.h"

#include "Debug.h"
#include "GraphicsEngine.h"

Framebuffer::Framebuffer(const FramebufferProfile& profile,
                         ID3D11Device* device) :
	profile{profile},
	frameTextureView{nullptr},
	renderTarget{nullptr},
	depthStencilView{nullptr}
{
	ID3D11Texture2D* renderTargetTexture;
	D3D11_TEXTURE2D_DESC renderTargetTextureDesc;
	ZeroMemory(&renderTargetTextureDesc, sizeof(renderTargetTextureDesc));
	HRESULT result;

	if (profile.TargetRenderTexture == nullptr)
	{
		renderTargetTextureDesc.Width            = this->profile.Width;
		renderTargetTextureDesc.Height           = this->profile.Height;
		renderTargetTextureDesc.MipLevels        = 1;
		renderTargetTextureDesc.ArraySize        = 1;
		renderTargetTextureDesc.Format           = DXGI_FORMAT_R32G32B32A32_FLOAT;
		renderTargetTextureDesc.SampleDesc.Count = 1;
		renderTargetTextureDesc.Usage            = D3D11_USAGE_DEFAULT;
		renderTargetTextureDesc.BindFlags        = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		renderTargetTextureDesc.CPUAccessFlags   = 0;
		renderTargetTextureDesc.MiscFlags        = 0;

		result = device->CreateTexture2D(&renderTargetTextureDesc,
		                                 nullptr,
		                                 &renderTargetTexture);
		Debug::Assert(SUCCEEDED(result), "Failed to create Frame texture!");
	}
	else
	{
		renderTargetTexture = this->profile.TargetRenderTexture;
		this->profile.TargetRenderTexture->GetDesc(&renderTargetTextureDesc);
	}

	//-----------------------------

	D3D11_RENDER_TARGET_VIEW_DESC renderTargetDesc;
	renderTargetDesc.Format             = renderTargetTextureDesc.Format;
	renderTargetDesc.ViewDimension      = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetDesc.Texture2D.MipSlice = 0;

	result = device->CreateRenderTargetView(renderTargetTexture,
	                                        &renderTargetDesc,
	                                        &renderTarget);
	Debug::Assert(SUCCEEDED(result), "Failed to create Render Target View!");
	renderTargetTexture->Release();

	//-----------------------------
	ID3D11Texture2D* depthStencilTexture = nullptr;
	D3D11_TEXTURE2D_DESC depthStencilTextureDesc;
	depthStencilTextureDesc.Width              = this->profile.Width;
	depthStencilTextureDesc.Height             = this->profile.Height;
	depthStencilTextureDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilTextureDesc.Usage              = D3D11_USAGE_DEFAULT;
	depthStencilTextureDesc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
	depthStencilTextureDesc.MipLevels          = 1;
	depthStencilTextureDesc.SampleDesc.Count   = 1;
	depthStencilTextureDesc.SampleDesc.Quality = 0;
	depthStencilTextureDesc.MiscFlags          = 0;
	depthStencilTextureDesc.ArraySize          = 1;
	depthStencilTextureDesc.CPUAccessFlags     = 0;

	result = device->CreateTexture2D(&depthStencilTextureDesc,
	                                 nullptr,
	                                 &depthStencilTexture);
	Debug::Assert(SUCCEEDED(result), "Failed to create Depth Stencil View Texture!");

	result = device->CreateDepthStencilView(depthStencilTexture,
	                                        nullptr,
	                                        &depthStencilView);
	Debug::Assert(SUCCEEDED(result), "Failed to create Depth Stencil View!");

	depthStencilTexture->Release();

	//-----------------------------

	if (this->profile.SwapChainFramebuffer)
		return;

	//-----------------------------

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format                    = renderTargetTextureDesc.Format;
	srvDesc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels       = 1;
	srvDesc.Texture2D.MostDetailedMip = 0;

	result = device->CreateShaderResourceView(renderTargetTexture,
	                                          &srvDesc,
	                                          &frameTextureView);
	Debug::Assert(SUCCEEDED(result), "Failed to create Frame Texture View!");
}

Framebuffer::~Framebuffer()
{
	if (frameTextureView != nullptr)
		frameTextureView->Release();

	if (renderTarget != nullptr)
		renderTarget->Release();

	if (depthStencilView != nullptr)
		depthStencilView->Release();
}

const FramebufferProfile& Framebuffer::getInfo() const
{
	return profile;
}

ID3D11ShaderResourceView& Framebuffer::getFrame() const
{
	return *frameTextureView;
}

ID3D11RenderTargetView& Framebuffer::getRenderTarget() const
{
	return *renderTarget;
}

ID3D11DepthStencilView& Framebuffer::getDepthStencil() const
{
	return *depthStencilView;
}
