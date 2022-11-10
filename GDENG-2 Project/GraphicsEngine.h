#pragma once
#include <d3d11.h>
#include "DeviceContext.h"

class SwapChain;
class DeviceContext;
class VertexBuffer;
class ConstantBuffer;

class GraphicsEngine final
{
public:
	static void init();
	static void release();

	[[nodiscard]]
	static GraphicsEngine* getInstance();

	[[nodiscard]]
	ID3D11Device& getDevice() const;

	[[nodiscard]]
	DeviceContext& getDeviceContext() const;

	[[nodiscard]]
	IDXGIFactory& getFactory() const;

	GraphicsEngine(const GraphicsEngine&)                = delete;
	GraphicsEngine& operator=(const GraphicsEngine&)     = delete;
	GraphicsEngine(GraphicsEngine&&) noexcept            = delete;
	GraphicsEngine& operator=(GraphicsEngine&&) noexcept = delete;

private:
	GraphicsEngine();
	~GraphicsEngine();

	static GraphicsEngine* instance;

	DeviceContext* immDeviceContext = nullptr;

	ID3D11Device* d3dDevice = nullptr;
	D3D_FEATURE_LEVEL featureLevel;

	IDXGIDevice* dxgiDevice   = nullptr;
	IDXGIAdapter* dxgiAdapter = nullptr;
	IDXGIFactory* dxgiFactory = nullptr;

	friend class SwapChain;
	friend class ConstantBuffer;
};
