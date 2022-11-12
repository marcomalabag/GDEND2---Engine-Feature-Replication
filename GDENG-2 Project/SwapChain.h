#pragma once
#include <d3d11.h>
class Framebuffer;
class DeviceContext;
class SwapChain final
{
public:
	SwapChain(HWND windowHandle,
	          unsigned int width,
	          unsigned int height,
	          ID3D11Device* device,
	          IDXGIFactory* factory);

	~SwapChain();

	[[nodiscard]]
	Framebuffer& getBuffer() const;

	void present(bool vsync) const;

	SwapChain(const SwapChain&)                = delete;
	SwapChain& operator=(const SwapChain&)     = delete;
	SwapChain(SwapChain&&) noexcept            = delete;
	SwapChain& operator=(SwapChain&&) noexcept = delete;

private:
	IDXGISwapChain* swapChain;
	Framebuffer* framebuffer;

	friend class DeviceContext;
};
