#pragma once
#include <Windows.h>

class Window
{
public:
	Window();
	virtual ~Window();

	bool initializeWC();
	bool initializeAppWindow();
	bool broadcast();
	bool release();
	bool isRun();

	HWND gethwnd();
	RECT getClientWindowRect();

	void setHandle(HWND hwnd);

	// Window Events

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	virtual void onFocus();
	virtual void onKillFocus();
	virtual void onResize(UINT width, UINT height);
	
protected:
	HWND hwnd;
	bool isRunning;
	UINT width;
	UINT height;
};
