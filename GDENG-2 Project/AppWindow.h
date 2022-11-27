#pragma once
#include "Window.h"

#include "Graphics/SwapChain.h"

class AppWindow final : public Window
{
public:
	static void initialize();
	static void terminate();
	
	static AppWindow* getInstance();

	void initializeEngine();
	void createInterface();

	void createInitialObjects();
	
	void onCreate() override;
	void onDestroy() override;
	void onUpdate() override;
	void onResize(UINT width, UINT height) override;
	// void onFocus() override;
	// void onKillFocus() override;

	AppWindow(const AppWindow&)                = delete;
	AppWindow& operator=(const AppWindow&)     = delete;
	AppWindow(AppWindow&&) noexcept            = delete;
	AppWindow& operator=(AppWindow&&) noexcept = delete;

private:
	AppWindow();
	~AppWindow();

private:
	static AppWindow* sharedInstance;
	SwapChain* swapChain;
};

