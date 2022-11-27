#include "AppWindow.h"

#include "ImGui/imgui.h"

#include "EngineTime.h"
#include "Graphics/GraphicsEngine.h"
#include "Graphics/ShaderLibrary.h"
// #include "UI/UIManager.h"
#include "Input/InputSystem.h"
#include "ECS/Core/GameObjectManager.h"
#include "ECS/Core/SystemManager.h"

#include "UI/SampleScreen.h"
#include "UI/UISystem.h"
#include "UI/ViewportScreen.h"

AppWindow* AppWindow::sharedInstance = nullptr;

AppWindow::AppWindow() :
	swapChain{nullptr} { }

AppWindow::~AppWindow() {}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
	sharedInstance->initializeWC();
	sharedInstance->initializeAppWindow();
}

void AppWindow::terminate()
{
	delete sharedInstance;
}

AppWindow* AppWindow::getInstance()
{
	if (sharedInstance != nullptr)
	{
		return sharedInstance;
	}
	return nullptr;
}

void AppWindow::onCreate()
{
	Window::onCreate();
	InputSystem::initialize();
	EngineTime::initialize();
}

void AppWindow::initializeEngine()
{
	GraphicsEngine::initialize();
	swapChain = GraphicsEngine::getInstance()->getDevice().createSwapChain(this->hwnd,
	                                                                       this->width,
	                                                                       this->height);
	ShaderLibrary::init(5);
	// SceneCameraHandler::init(width, height);
	// GameCameraHandler::initialize(width, height);
	GameObjectManager::initialize();
	SystemManager::initialize();
}

void AppWindow::createInterface()
{
	UISystem::initialize(this->hwnd, this->width, this->height);
}

void AppWindow::createInitialObjects()
{
	//ShaderLibrary::add<VertexShader>("GDENG-2 Project/Assets/SolidColor_VS.hlsl");
	//ShaderLibrary::add<PixelShader>("GDENG-2 Project/Assets/SolidColor_PS.hlsl");

	UISystem::getInstance()->createUI<SampleScreen>();
	UISystem::getInstance()->createUI<ViewportScreen>();
	UISystem::getInstance()->createUI<ViewportScreen>();

	// Initial Entities
	// Goal: Draw at least 1 Cube using ECS
	// GameObjectManager::getInstance()->createObject(GameObjectManager::CUBE);
	// GameCameraHandler::getInstance()->initializeGameCamera();
}

void AppWindow::onUpdate()
{
	//=====PROCESS INPUT=====//
	//Window::onUpdate();
	InputSystem::getInstance()->update(); // May need refactoring if the InputSystem implementation changes.

	//=====PROCESS GAME OBJECT AWAKE()/START()=====//
	// TODO?

	//=====PROCESS GAME OBJECT UPDATE()=====//
	// TODO?

	//=====PROCESS GAME OBJECT MOVEMENT AND RESOLVE COLLISIONS=====//
	// Technically, we can have game camera have collisions and be moved here?
	// TODO?

	//=====PROCESS CAMERA LOGIC=====//
	// SystemManager::getCameraSystem().editorCameraUpdate(); // With given inputs to the focused camera, move and rotate accordingly.
	// SystemManager::getCameraSystem().gameCameraUpdate(); // For this case, this is where the actual set of Align with View implementation takes place

	//=====PROCESS POST-CAMERA LOGIC FOR GAME OBJECTS=====//
	// SystemManager::update();

	//=====PROCESS VIEWPORT LOGIC=====//
	// UISystem::getViewportSystem().update(); // Mainly, resize events
	// If the viewport's size is not equal owned camera's size: set Viewport size to the owned camera size

	//=====DRAWING=====//
	const Framebuffer& swapChainFramebuffer = this->swapChain->getBuffer();
	GraphicsEngine::getInstance()->getDeviceContext().setViewportSize((float)swapChainFramebuffer.getInfo().Width,
	                                                                  (float)swapChainFramebuffer.getInfo().Height);
	GraphicsEngine::getInstance()->getDeviceContext().setRenderTarget(&swapChainFramebuffer.getRenderTarget(),
	                                                                  &swapChainFramebuffer.getDepthStencil());
	GraphicsEngine::getInstance()->getDeviceContext().clearRenderTargetView(swapChainFramebuffer.getRenderTarget(),
	                                                                        Color(1.0, 0, 0, 1));
	GraphicsEngine::getInstance()->getDeviceContext().clearDepthStencilView(swapChainFramebuffer.getDepthStencil());

	// Draw to Each Viewport using Camera's Framebuffer
	// foreach (viewport : ViewportList)
	// {
	//		viewport.Camera.BindFramebuffer();
	//		viewport.Camera.SetViewportSize();
	//		viewport.Camera.ClearFramebuffer();
	//
	//		RenderSystem::DrawObjects(viewport.Camera());
	//	
	//		viewport.UnbindFramebuffer();
	// }

	GraphicsEngine::getInstance()->getDeviceContext().setRenderTarget(&swapChainFramebuffer.getRenderTarget(),
																	  &swapChainFramebuffer.getDepthStencil());
	
	UISystem::getInstance()->drawAllUI(); 	// Draw each Viewport ImGui Image (included here)

	// If during draw shows that a ViewportSize is not equal to CameraSize
	// Request camera resize in the next frame.

	swapChain->present(true);
}

void AppWindow::onResize(const UINT width, const UINT height)
{
	Window::onResize(width, height);

	if (GraphicsEngine::getInstance() != nullptr)
	{
		this->swapChain->resize(width, height,
		                        GraphicsEngine::getInstance()->getDeviceContext(),
		                        GraphicsEngine::getInstance()->getDevice());
	}

	if (UISystem::getInstance() != nullptr)
	{
		UISystem::getInstance()->resizeContext(this->width, this->height);
	}
}

void AppWindow::onDestroy()
{
	SystemManager::terminate();

	GameObjectManager::terminate();

	ShaderLibrary::release();

	// UIManager::destroy();

	delete swapChain;

	GraphicsEngine::terminate();

	InputSystem::destroy();

	Window::onDestroy();
}

// void AppWindow::onFocus()
// {
// 	InputSystem::getInstance()->addListener(this);
// }
//
// void AppWindow::onKillFocus()
// {
// 	InputSystem::getInstance()->removeListener(this);
// }
