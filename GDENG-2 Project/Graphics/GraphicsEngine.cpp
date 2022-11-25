#include "GraphicsEngine.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <vector>
#include "Debug.h"

GraphicsEngine* GraphicsEngine::instance = nullptr;

GraphicsEngine::GraphicsEngine() :
	renderDevice{nullptr},
	renderContext{nullptr}
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

	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;
	D3D_FEATURE_LEVEL featureLevel;

	for (const auto driverType : driverTypes)
	{
		result = D3D11CreateDevice(nullptr,
		                           driverType,
		                           nullptr,NULL,
		                           featureLevels.data(),
		                           (UINT)featureLevels.size(),
		                           D3D11_SDK_VERSION,
		                           &device,
		                           &featureLevel,
		                           &deviceContext);
		if (SUCCEEDED(result))
		{
			break;
		}
	}

	Debug::Assert(SUCCEEDED(result), "Failed to create device!");

	this->renderDevice = new RenderDevice(device);
	this->renderContext = new RenderContext(deviceContext);
}

GraphicsEngine::~GraphicsEngine()
{
	delete renderContext;
	delete renderDevice;
}

void GraphicsEngine::initialize()
{
	if (instance == nullptr)
	{
		instance = new GraphicsEngine();
	}
}

void GraphicsEngine::terminate()
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

RenderDevice& GraphicsEngine::getDevice() const
{
	return *renderDevice;
}

RenderContext& GraphicsEngine::getDeviceContext() const
{
	return *renderContext;
}

