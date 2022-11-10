#include "GraphicsEngine.h"
#include "SwapChain.h"
#include <d3dcompiler.h>
#include <vector>

#include "Debug.h"

GraphicsEngine* GraphicsEngine::instance = nullptr;

GraphicsEngine::GraphicsEngine()
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
		                           &d3dDevice,
		                           &featureLevel,
		                           &deviceContext);
		if (SUCCEEDED(result))
		{
			break;
		}
	}

	Debug::Assert(SUCCEEDED(result), "Failed to create device!");

	this->immDeviceContext = new DeviceContext(deviceContext);

	d3dDevice->QueryInterface(__uuidof(IDXGIDevice),
	                          (void**)&dxgiDevice);
	dxgiDevice->GetParent(__uuidof(IDXGIAdapter),
	                      (void**)&dxgiAdapter);
	dxgiAdapter->GetParent(__uuidof(IDXGIFactory),
	                       (void**)&dxgiFactory);
}

GraphicsEngine::~GraphicsEngine()
{
	dxgiAdapter->Release();
	dxgiDevice->Release();
	dxgiFactory->Release();
	delete immDeviceContext;
	d3dDevice->Release();
}

void GraphicsEngine::init()
{
	if (instance == nullptr)
	{
		instance = new GraphicsEngine();
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
