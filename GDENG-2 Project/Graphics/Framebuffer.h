#pragma once
#include <d3d11.h>

struct FramebufferProfile
{
	unsigned int Width = 512;
	unsigned int Height = 512;
	ID3D11Texture2D* TargetRenderTexture = nullptr;
	bool SwapChainFramebuffer            = false;
};

class Framebuffer final
{
public:
	explicit Framebuffer(ID3D11Device& device,
	                     const FramebufferProfile& profile);
	~Framebuffer();

	[[nodiscard]]
	const FramebufferProfile& getInfo() const;

	ID3D11ShaderResourceView& getFrame() const;

	ID3D11RenderTargetView& getRenderTarget() const;

	ID3D11DepthStencilView& getDepthStencil() const;

	Framebuffer(const Framebuffer&)                = delete;
	Framebuffer& operator=(const Framebuffer&)     = delete;
	Framebuffer(Framebuffer&&) noexcept            = delete;
	Framebuffer& operator=(Framebuffer&&) noexcept = delete;
private:
	FramebufferProfile profile;

	ID3D11ShaderResourceView* frameTextureView;
	ID3D11RenderTargetView* renderTarget;
	ID3D11DepthStencilView* depthStencilView;
};
