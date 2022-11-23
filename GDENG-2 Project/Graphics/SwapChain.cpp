#include "SwapChain.h"
#include "Debug.h"

#include "Graphics/Framebuffer.h"

SwapChain::SwapChain(ID3D11Device& device,
                     IDXGIFactory& factory,
                     HWND windowHandle,
                     unsigned int width,
                     unsigned int height)
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferDesc.Width  = width;
	desc.BufferDesc.Height = height;

	desc.BufferDesc.RefreshRate.Numerator   = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;

	desc.BufferDesc.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	desc.BufferDesc.Scaling          = DXGI_MODE_SCALING_CENTERED;

	desc.SampleDesc.Count   = 1;
	desc.SampleDesc.Quality = 0;
	desc.BufferCount        = 1;

	desc.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
	desc.OutputWindow = windowHandle;

	desc.Windowed = TRUE;

	HRESULT result = factory.CreateSwapChain(&device, &desc, &swapChain);

	Debug::Assert(SUCCEEDED(result), "Failed to create swap chain!");

	ID3D11Texture2D* buffer = nullptr;
	result                  = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
	Debug::Assert(SUCCEEDED(result), "Failed to get swap chain buffer!");

	FramebufferProfile swapChainFramebufferProfile;
	swapChainFramebufferProfile.Width                = width;
	swapChainFramebufferProfile.Height               = height;
	swapChainFramebufferProfile.SwapChainFramebuffer = true;
	swapChainFramebufferProfile.TargetRenderTexture  = buffer;

	this->framebuffer = new Framebuffer(device, swapChainFramebufferProfile);
}

void SwapChain::present(const bool vsync) const
{
	this->swapChain->Present(vsync, NULL);
}

SwapChain::~SwapChain()
{
	delete this->framebuffer;
	if (this->swapChain != nullptr)
		this->swapChain->Release();
}

Framebuffer& SwapChain::getBuffer() const
{
	return *this->framebuffer;
}
