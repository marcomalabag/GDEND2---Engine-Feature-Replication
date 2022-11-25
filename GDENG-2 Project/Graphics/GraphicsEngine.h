#pragma once
#include "RenderContext.h"
#include "RenderDevice.h"

class GraphicsEngine final
{
public:
	static void initialize();
	static void terminate();

	static GraphicsEngine* getInstance();

	RenderDevice& getDevice() const;

	RenderContext& getDeviceContext() const;

	GraphicsEngine(const GraphicsEngine&)                = delete;
	GraphicsEngine& operator=(const GraphicsEngine&)     = delete;
	GraphicsEngine(GraphicsEngine&&) noexcept            = delete;
	GraphicsEngine& operator=(GraphicsEngine&&) noexcept = delete;

private:
	GraphicsEngine();
	~GraphicsEngine();

	static GraphicsEngine* instance;

	RenderDevice* renderDevice;
	RenderContext* renderContext;
};