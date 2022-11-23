#pragma once
#include <d3d11.h>
class Framebuffer;
class DeviceContext;
class SwapChain final
{
public:
	SwapChain(ID3D11Device& device,
			  IDXGIFactory& factory,
			  HWND windowHandle,
	          unsigned int width,
	          unsigned int height);

	~SwapChain();

	[[nodiscard]]
	Framebuffer& getBuffer() const;

	void present(bool vsync) const;

	SwapChain(const SwapChain&)                = delete;
	SwapChain& operator=(const SwapChain&)     = delete;
	SwapChain(SwapChain&&) noexcept            = delete;
	SwapChain& operator=(SwapChain&&) noexcept = delete;

private:
	IDXGISwapChain* swapChain = nullptr;
	Framebuffer* framebuffer = nullptr;

	friend class DeviceContext;
};
