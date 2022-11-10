#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Vector3D.h"
#include <vector>
#include "UIManager.h"
#include "Cube.h"
#include "EngineTime.h"
#include "InputListener.h"
#include "InputSystem.h"

class AppWindow : public Window, public InputListener
{
public:

	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;

	void onFocus() override;
	void onKillFocus() override;

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& deltaMousePos) override;
	virtual void onLeftMouseDown(const Point& mousePosition) override;
	virtual void onLeftMouseUp(const Point& mousePosition) override;
	virtual void onRightMouseDown(const Point& mousePosition) override;
	virtual void onRightMouseUp(const Point& mousePosition) override;

	void initializeEngine();
	void createInterface();

public:
	static void initialize();
	static AppWindow* getInstance();

private:
	AppWindow();
	~AppWindow();
	AppWindow(AppWindow const&){};
	AppWindow&operator=(AppWindow const&){};

private:
	static AppWindow* sharedInstance;

private:
	SwapChain* swapChain;
	Cube* cube;
	unsigned long oldTime = 0;
	float deltaTime = 0;
	float angle = 0;
	float ticks = 0.0f;
};

