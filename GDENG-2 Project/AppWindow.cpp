#include "AppWindow.h"
#include "IMGUI/imgui.h"

#include "Mathf.h"
#include "ShaderLibrary.h"

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
	ShaderLibrary::init(5);
	EngineTime::initialize();
	SceneCameraHandler::initialize();
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();

	Viewport::initialize();

	m_swap_chain = graphEngine->createSwapChain();

	RECT rc    = this->getClientWindowRect();
	int width  = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	m_swap_chain->init(this->m_hwnd, width, height);

	Viewport::getInstance()->add((FLOAT)width, (FLOAT)height, 0.0f,
	                             1.0f, 0.0f, 0.0f);

	positions[0] = Vector3D(-.5, .25, 0.0);
	positions[1] = Vector3D(.5, .25, 0.0);
	positions[2] = Vector3D(0, -.25, 0.0);

	ShaderLibrary::add<VertexShader>("Assets/VertexShader.hlsl");
	ShaderLibrary::add<PixelShader>("Assets/PixelShader.hlsl");

	this->vertexshader = &ShaderLibrary::getShader<VertexShader>("VertexShader");
	this->pixelshader = &ShaderLibrary::getShader<PixelShader>("PixelShader.hlsl");

	void* shader_byte_code = nullptr;
	size_t size_shader     = 0;

	//For instantiating rectangles
	float max = 1.5f;
	float min = -2.5f;

	for (int i = 0; i < 1; i++)
	{
		float x = Mathf::getRandom(min, max);
		float y = Mathf::getRandom(-2.0, 1.0f);

		float speed = Mathf::getRandom(1.0f, 25.0f);
		this->Cubes.push_back(new Cube("Cube", shader_byte_code, size_shader));
		this->Cubes.at(i)->setScale(.5, .5, .5);
		this->Cubes.at(i)->setPosition(0.0f, 1.0f, 3.0f);
		this->Cubes.at(i)->setAnimSpeed(speed);
	}

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

	GraphicsEngine::getInstance()->getDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
	                                                                                   0, 0, 0.5, 0.5);
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getDeviceContext()->
	                               setViewportSize(Viewport::getInstance()->getViewport(0));

	for (int i = 0; i < Cubes.size(); i++)
	{
		//Cubes[i]->update(ticks);
		Cubes.at(i)->draw(rc.right - rc.left, rc.bottom - rc.top, this->vertexshader, this->pixelshader);
	}

	SceneCameraHandler::getInstance()->update();
	UIManager::getInstance()->drawAllUI();

	this->m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	m_swap_chain->release();

	InputSystem::destroy();

	ShaderLibrary::release();

	if (GraphicsEngine::getInstance() != NULL)
	{
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
	if (sharedInstance != NULL)
	{
		return sharedInstance;
	}
	return nullptr;
}
