#pragma once
#include <Windows.h>
#include "EngineTime.h"

class Window
{
public:
	Window();
	bool initializeWC();
	bool initializeAppWindow();
	bool initiazeGameWindow();
	bool broadcast();
	bool release();
	bool isRun();
	bool isGameRun();

	HWND gethwnd();
	RECT getClientWindowRect();
	
	void setHandle(HWND hwnd);

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();

	virtual void onFocus();
	virtual void onKillFocus();


	virtual ~Window();

protected:
	HWND hwnd;
	bool isRunning;
};

