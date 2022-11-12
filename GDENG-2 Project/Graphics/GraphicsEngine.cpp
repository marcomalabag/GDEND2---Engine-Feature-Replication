#include "GraphicsEngine.h"
#include "SwapChain.h"
#include <d3dcompiler.h>
#include <vector>

#include "Debug.h"

GraphicsEngine* GraphicsEngine::instance = nullptr;

GraphicsEngine::GraphicsEngine(const HWND windowHandle,
                               const unsigned int width,
                               const unsigned int height) :
	swapChain{nullptr},
	immDeviceContext{nullptr},
	d3dDevice{nullptr},
	dxgiDevice{nullptr},
	dxgiAdapter{nullptr},
	dxgiFactory{nullptr}
{
	const std::vector<D3D_DRIVER_TYPE> driverTypes =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	const std::vector<D3D_FEATURE_LEVEL> featureLevels =
	{
		D3D_FEATURE_LEVEL_11_0
	};

	HRESULT result = 0;

	ID3D11DeviceContext* deviceContext = nullptr;

	for (const auto driverType : driverTypes)
	{
		result = D3D11CreateDevice(nullptr,
		                           driverType,
		                           nullptr,NULL,
		                           featureLevels.data(),
		                           (UINT)featureLevels.size(),
		                           D3D11_SDK_VERSION,
		                           &this->d3dDevice,
		                           &this->featureLevel,
		                           &deviceContext);
		if (SUCCEEDED(result))
		{
			break;
		}
	}

	Debug::Assert(SUCCEEDED(result), "Failed to create device!");

	this->immDeviceContext = new DeviceContext(deviceContext);

	this->d3dDevice->QueryInterface(__uuidof(IDXGIDevice),
	                                (void**)&this->dxgiDevice);
	this->dxgiDevice->GetParent(__uuidof(IDXGIAdapter),
	                            (void**)&this->dxgiAdapter);
	this->dxgiAdapter->GetParent(__uuidof(IDXGIFactory),
	                             (void**)&this->dxgiFactory);

	this->swapChain = new SwapChain(windowHandle,
	                                width,
	                                height,
	                                this->d3dDevice,
	                                this->dxgiFactory);
}

GraphicsEngine::~GraphicsEngine()
{
	delete this->swapChain;
	this->dxgiAdapter->Release();
	this->dxgiDevice->Release();
	this->dxgiFactory->Release();
	delete this->immDeviceContext;
	this->d3dDevice->Release();
}

void GraphicsEngine::init(const HWND windowHandle,
                          const unsigned int width,
                          const unsigned int height)
{
	if (instance == nullptr)
	{
		instance = new GraphicsEngine(windowHandle, width, height);
	}
}

void GraphicsEngine::release()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

GraphicsEngine* GraphicsEngine::getInstance()
{
	if (instance != nullptr)
	{
		return instance;
	}
	return nullptr;
}

ID3D11Device& GraphicsEngine::getDevice() const
{
	return *this->d3dDevice;
}

DeviceContext& GraphicsEngine::getDeviceContext() const
{
	return *this->immDeviceContext;
}
IDXGIFactory& GraphicsEngine::getFactory() const
{
	return *this->dxgiFactory;
}
SwapChain& GraphicsEngine::getSwapChain() const
{
	return *this->swapChain;
}
