#include "AppWindow.h"
#include "IMGUI/imgui.h"



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

	Viewport::initialize();

	m_swap_chain = graphEngine->createSwapChain();

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	m_swap_chain->init(this->m_hwnd, width, height);

	Viewport::getInstance()->add((FLOAT)width, (FLOAT)height, 0.0f,
		1.0f, 0.0f, 0.0f);


	positions[0] = Vector3D(-.5, .25, 0.0);
	positions[1] = Vector3D(.5, .25, 0.0);
	positions[2] = Vector3D(0, -.25, 0.0);

	/*
	TrianglePositions[0] = Vector3D(-.5, .5, 0.0);
	TrianglePositions[1] = Vector3D(.5, .5, 0.0);
	TrianglePositions[2] = Vector3D(0, .001, 0.0);
	*/

	//For instantiating triangles
	/*
	for(int i = 0; i < 3; i++)
	{
		this->triangle.push_back(new Triangle());
		this->triangle.at(i)->setPosition(TrianglePositions[i]);
		this->triangle.at(i)->setWindowSizeHeight((rc.bottom - rc.top) / 400.f);
		this->triangle.at(i)->setWindowSizeLength((rc.right - rc.left) / 400.f);
	}
	*/
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	this->vertexshader = graphEngine->createVertexShader(shader_byte_code, size_shader);


	//For instantiating rectangles
	int max = 1.5f;
	int min = -2.5f;
	Math math;

	for (int i = 0; i < 1; i++)
	{
		float x = math.getRandom(min, max);
		float y = math.getRandom(-2.0, 1.0f);

		float speed = math.getRandom(1.0f, 25.0f);
		this->Cubes.push_back(new Cube("Cube", shader_byte_code, size_shader));
		this->Cubes.at(i)->setScale(.5, .5, .5);
		this->Cubes.at(i)->setPosition(0.0f, 1.0f, 3.0f);
		this->Cubes.at(i)->setAnimSpeed(speed);

	}

	graphEngine->releaseCompiledShader();


	graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	this->pixelshader = graphEngine->createPixelShader(shader_byte_code, size_shader);


	graphEngine->releaseCompiledShader();
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
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(Viewport::getInstance()->getViewport(0));

	//For instantiating triangles
	/*
	for(int i = 0; i < this->triangle.size(); i++)
	{
		this->triangle.at(i)->draw();
	}
	*/
	
	for (int i = 0; i < Cubes.size(); i++)
	{

		//Cubes[i]->update(ticks);
		Cubes.at(i)->draw(rc.right - rc.left, rc.bottom - rc.top, this->vertexshader, this->pixelshader);
	}

	SceneCameraHandler::getInstance()->update();
	UIManager::getInstance()->drawAllUI();
	
	

	this->m_swap_chain->present(true);

	//this->m_swap_chain_game->present(false);
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
