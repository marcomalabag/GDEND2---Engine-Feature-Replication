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
	
	void setHWND(HWND hwnd);

	

	//virtual methods
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();

	virtual void onFocus();
	virtual void onKillFocus();


	~Window();

protected:
	HWND m_hwnd;
	//HWND m_gamewindow;
	bool m_isRunning;
	//bool GameWindowRunning;

};

