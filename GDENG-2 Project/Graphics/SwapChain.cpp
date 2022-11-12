#include "SwapChain.h"
#include "Debug.h"

#include "RenderView/Framebuffer.h"

SwapChain::SwapChain(HWND windowHandle,
                     unsigned int width,
                     unsigned int height,
                     ID3D11Device* device,
                     IDXGIFactory* factory)
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount                        = 1;
	desc.BufferDesc.Width                   = width;
	desc.BufferDesc.Height                  = height;
	desc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator   = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow                       = windowHandle;
	desc.SampleDesc.Count                   = 1;
	desc.SampleDesc.Quality                 = 0;
	desc.Windowed                           = TRUE;

	HRESULT result = factory->CreateSwapChain(device, &desc, &swapChain);

	Debug::Assert(SUCCEEDED(result), "Failed to create swap chain!");

	ID3D11Texture2D* buffer = nullptr;

	result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	Debug::Assert(SUCCEEDED(result), "Failed to get swap chain buffer!");

	FramebufferProfile swapChainFramebufferProfile;
	swapChainFramebufferProfile.Width                = width;
	swapChainFramebufferProfile.Height               = height;
	swapChainFramebufferProfile.SwapChainFramebuffer = true;
	swapChainFramebufferProfile.TargetRenderTexture  = buffer;

	this->framebuffer = new Framebuffer(swapChainFramebufferProfile,
	                                    device);
}

void SwapChain::present(const bool vsync) const
{
	this->swapChain->Present(vsync, NULL);
}

SwapChain::~SwapChain()
{
	delete this->framebuffer;
	this->swapChain->Release();
}

Framebuffer& SwapChain::getBuffer() const
{
	return *this->framebuffer;
}
