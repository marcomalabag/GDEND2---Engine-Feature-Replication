#include "AppWindow.h"
#include "IMGUI/imgui.h"

#include "Mathf.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};

__declspec(align(16))
struct constant
{
	float m_angle;
};


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
	GraphicsEngine::initialize();
	EngineTime::initialize();
	SceneCameraHandler::initialize();
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();
	GameObjectManager::initialize();
	GameCameraHandler::initialize();

	Viewport::initialize();



	m_swap_chain = graphEngine->createSwapChain();

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	m_swap_chain->init(this->m_hwnd, width, height);

	Viewport::getInstance()->add((FLOAT)width, (FLOAT)height, 0.0f,
		1.0f, 0.0f, 0.0f);

	//GameObjectManager::getInstance()->createObject(GameObjectManager::CUBE);
	GameCameraHandler::getInstance()->initializeGameCamera();
	
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
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0, 0.5, 0.5);
	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(Viewport::getInstance()->getViewport(0));

	
	GameObjectManager::getInstance()->renderAll(width, height);

	SceneCameraHandler::getInstance()->update();
	UIManager::getInstance()->drawAllUI();
	
	

	this->m_swap_chain->present(true);

	
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	//this->vertexbuffer->release();

	
	m_swap_chain->release();
	
	InputSystem::destroy();
	//this->vertexshader->release();
	//this->pixelshader->release();
	if (GraphicsEngine::getInstance() != NULL) {
		GraphicsEngine::getInstance()->release();
	}
	
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
	if(sharedInstance != NULL)
	{
		return sharedInstance;
	}
}
