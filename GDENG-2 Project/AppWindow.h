#pragma once
#include "Window.h"
#include "Graphics/GraphicsEngine.h"
#include "Graphics/SwapChain.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/ConstantBuffer.h"
#include "Graphics/VertexShader.h"
#include "Graphics/PixelShader.h"
#include <vector>
#include "UI/UIManager.h"
#include "EngineTime.h"
#include "InputListener.h"
#include "InputSystem.h"
#include "GameCameraHandler.h"

class AppWindow final : public Window, public InputListener
{
public:
	static void initialize();
	static void terminate();
	
	static AppWindow* getInstance();
	
	void onCreate() override;
	void onDestroy() override;
	void onUpdate() override;
	void onResize() override;
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

	AppWindow(const AppWindow&)                = delete;
	AppWindow& operator=(const AppWindow&)     = delete;
	AppWindow(AppWindow&&) noexcept            = delete;
	AppWindow& operator=(AppWindow&&) noexcept = delete;

private:
	AppWindow();
	~AppWindow();

private:
	static AppWindow* sharedInstance;

};

