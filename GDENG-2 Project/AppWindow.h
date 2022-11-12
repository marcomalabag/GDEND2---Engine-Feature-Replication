#pragma once
#include "Window.h"
#include "Graphics/GraphicsEngine.h"
#include "Graphics/SwapChain.h"
#include "Graphics/DeviceContext.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/ConstantBuffer.h"
#include "Graphics/VertexShader.h"
#include "Graphics/PixelShader.h"
#include "Math/Vector3D.h"
#include <vector>
#include "UI/UIManager.h"
#include "EngineTime.h"
#include "InputListener.h"
#include "InputSystem.h"
#include "GameObject/GameObjectManager.h"
#include "GameCameraHandler.h"

class HalfRenderQuad;
class RenderQuad;
class Cube;
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
	Cube* cube = nullptr;
	Framebuffer* framebuffer1 = nullptr;
	RenderQuad* renderQuad = nullptr;
	HalfRenderQuad* halfRenderQuad = nullptr;
	unsigned long oldTime = 0;
	float deltaTime = 0;
	float angle = 0;
	float ticks = 0.0f;
};

