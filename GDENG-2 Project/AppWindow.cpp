#include "AppWindow.h"

#include "IMGUI/imgui.h"

#include "Graphics/GraphicsEngine.h"
#include "SceneCameraHandler.h"

#include "Component/TransformComponent.h"

#include "Graphics/ShaderLibrary.h"

#include "GameObject/Cube.h"

#include "Graphics/RenderQuad.h"

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
	RECT rc    = this->getClientWindowRect();
	int width  = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	GraphicsEngine::init(this->hwnd, width, height);
	ShaderLibrary::init(5);
	EngineTime::initialize();
	SceneCameraHandler::initialize();
	GameCameraHandler::initialize();
	GameObjectManager::initialize();

	SystemHandler::init();

	ShaderLibrary::add<VertexShader>("GDENG-2 Project/Assets/SolidColor_VS.hlsl");
	ShaderLibrary::add<PixelShader>("GDENG-2 Project/Assets/SolidColor_PS.hlsl");

	cube = new Cube("Testing cube");
	cube->transform().Scale = Vector3D(5, 5, 5);

	FramebufferProfile framebuffer1Profile;
	framebuffer1Profile.Width  = width;
	framebuffer1Profile.Height = height;

	framebuffer1 = new Framebuffer(framebuffer1Profile,
	                               &GraphicsEngine::getInstance()->getDevice());

	renderQuad = new RenderQuad();

	// Initial Entities
	// Goal: Draw at least 1 Cube using ECS
	//GameObjectManager::getInstance()->createObject(GameObjectManager::CUBE);
	GameCameraHandler::getInstance()->initializeGameCamera();
	
}

void AppWindow::createInterface()
{
	UIManager::initialize(this->hwnd);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::getInstance()->update();

	this->ticks += EngineTime::getDeltaTime() * 1.0f;

	SceneCameraHandler::getInstance()->update();
	GameCameraHandler::getInstance()->update();

	// Drawing----------------
	//GameObjectManager::getInstance()->renderAll(width, height);

	Framebuffer& swapChainBuffer = GraphicsEngine::getInstance()->getSwapChain().getBuffer();
	FramebufferProfile swapChainBufferInfo = swapChainBuffer.getInfo();
	
	// GraphicsEngine::getInstance()->getDeviceContext().setViewportSize((float)swapChainBufferInfo.Width,
	// 																  (float)swapChainBufferInfo.Height);
	//
	// GraphicsEngine::getInstance()->getDeviceContext().setRenderTargetTo(&swapChainBuffer.getRenderTarget(),
	// 															&swapChainBuffer.getDepthStencil());
	//
	// GraphicsEngine::getInstance()->getDeviceContext().clearRenderTargetView(swapChainBuffer.getRenderTarget(),
	// 																	Color(0.8f, 0.4f, 0.7f, 1.0f));
	//
	// GraphicsEngine::getInstance()->getDeviceContext().clearDepthStencilView(swapChainBuffer.getDepthStencil());

	SystemHandler::getInstance().getRenderSystem().draw(&swapChainBuffer);

	// // Draw quad with texture of the framebuffer
	// renderQuad->draw(framebuffer1->getFrame());

	UIManager::getInstance()->drawAllUI();

	GraphicsEngine::getInstance()->getSwapChain().present(true);
}

void AppWindow::onDestroy()
{
	delete framebuffer1;

	// delete renderQuad;
	
	SystemHandler::release();

	Window::onDestroy();

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
