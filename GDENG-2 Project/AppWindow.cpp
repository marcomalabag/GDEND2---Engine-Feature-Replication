#include "AppWindow.h"

#include "RenderComponent.h"

#include "IMGUI/imgui.h"

#include "SceneCameraHandler.h"
#include "ShaderLibrary.h"

AppWindow* AppWindow::sharedInstance = NULL;

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
	sharedInstance->initializeWC();
	sharedInstance->initializeAppWindow();
}

void AppWindow::onCreate()
{
	Window::onCreate();
	InputSystem::initialize();
}

void AppWindow::initializeEngine()
{
	GraphicsEngine::init();
	ShaderLibrary::init(5);
	EngineTime::initialize();
	SceneCameraHandler::initialize();

	swapChain = new SwapChain();

	RECT rc    = this->getClientWindowRect();
	int width  = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	swapChain->init(this->m_hwnd, width, height);

	ShaderLibrary::add<VertexShader>("GDENG-2 Project/Assets/SolidColor_VS.hlsl");
	ShaderLibrary::add<PixelShader>("GDENG-2 Project/Assets/SolidColor_PS.hlsl");

	cube = new Cube("Testing cube");
	// this->vertexshader = &ShaderLibrary::getShader<VertexShader>("VertexShader");
	// this->pixelshader = &ShaderLibrary::getShader<PixelShader>("PixelShader.hlsl");

	// Initial Entities
	// Goal: Draw at least 1 Cube using ECS
}

void AppWindow::createInterface()
{
	UIManager::initialize(this->m_hwnd);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::getInstance()->update();

	this->ticks += EngineTime::getDeltaTime() * 1.0f;

	// Drawing----------------
	GraphicsEngine::getInstance()->getDeviceContext().clearRenderTargetColor(swapChain,
	                                                                         0.8f,
	                                                                         0.3f,
	                                                                         0.6f,
	                                                                         1.0f);

	// GraphicsEngine::getInstance()->getDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
	//                                                                                    0, 0, 0.5, 0.5);
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getDeviceContext().
	                               setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	cube->getComponent<RenderComponent>()->draw(SceneCameraHandler::getInstance()->getSceneCameraViewMatrix());

	SceneCameraHandler::getInstance()->update();
	UIManager::getInstance()->drawAllUI();

	this->swapChain->present(true);
}

void AppWindow::onDestroy()
{
	delete cube;
	Window::onDestroy();

	swapChain->release();

	InputSystem::destroy();

	ShaderLibrary::release();

	GraphicsEngine::getInstance()->release();

	UIManager::getInstance()->destroy();
}

void AppWindow::onFocus()
{
	InputSystem::getInstance()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::getInstance()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
}

void AppWindow::onKeyUp(int key)
{
}

void AppWindow::onMouseMove(const Point& deltaMousePos)
{
}

void AppWindow::onLeftMouseDown(const Point& mousePosition)
{
}

void AppWindow::onLeftMouseUp(const Point& mousePosition)
{
}

void AppWindow::onRightMouseDown(const Point& mousePosition)
{
}

void AppWindow::onRightMouseUp(const Point& mousePosition)
{
}

AppWindow* AppWindow::getInstance()
{
	if (sharedInstance != NULL)
	{
		return sharedInstance;
	}
	return nullptr;
}
