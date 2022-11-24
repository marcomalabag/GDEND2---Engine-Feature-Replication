#include "Window.h"
#include <iostream>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//Window* window = nullptr;
Window::Window() {}

LRESULT CALLBACK wndProc(const HWND hwnd, const UINT msg,
                         const WPARAM wparam, const LPARAM lparam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
		return true;

	switch (msg)
	{
		case WM_CREATE:
		{
			Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
			window->setHandle(hwnd);
			window->onCreate();
			break;
		}
		case WM_DESTROY:
		{
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onDestroy();
			::PostQuitMessage(0);
			break;
		}
		case WM_SETFOCUS:
		{
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onFocus();
			break;
		}

		case WM_KILLFOCUS:
		{
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onKillFocus();
			break;
		}
		case WM_SIZE:
		{
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onResize();
		}
		default:
		{
			return ::DefWindowProc(hwnd, msg, wparam, lparam);
		}
	}

	return NULL;
}

bool Window::initializeWC()
{
	WNDCLASSEX wc;
	wc.cbClsExtra    = NULL;
	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.cbWndExtra    = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance     = NULL;
	wc.lpszClassName = L"GDENG - 2 Project";
	wc.lpszMenuName  = L"";
	wc.style         = NULL;
	wc.lpfnWndProc   = &wndProc;

	if (!::RegisterClassEx(&wc))
	{
		return false;
	}
}

bool Window::initializeAppWindow()
{
	this->hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"GDENG - 2 Project", L"DirectX Application",
	                              WS_OVERLAPPEDWINDOW,
	                              CW_USEDEFAULT, CW_USEDEFAULT, 1440, 900, NULL, NULL, NULL, this);

	if (!this->hwnd)
	{
		std::cout << "Not working";
		return false;
	}

	::ShowWindow(this->hwnd, SW_SHOW);
	::UpdateWindow(this->hwnd);

	isRunning = true;

	return true;
}

bool Window::broadcast()
{
	MSG msg;
	EngineTime::LogFrameStart();
	this->onUpdate();

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(1);
	EngineTime::LogFrameEnd();
	return true;
}

bool Window::release()
{
	if (!::DestroyWindow(this->hwnd))
	{
		return false;
	}

	/*
	if (!::DestroyWindow(this->m_gamewindow)) {
		return false;
	}
	*/
	return true;
}

bool Window::isRun()
{
	return isRunning;
}

HWND Window::gethwnd()
{
	return hwnd;
}

RECT Window::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->hwnd, &rc);
	return rc;
}

void Window::setHandle(HWND hwnd)
{
	this->hwnd = hwnd;
}

Window::~Window() {}

void Window::onCreate() {}

void Window::onUpdate() { }

void Window::onFocus() {}

void Window::onKillFocus() {}

void Window::onResize(UINT width, UINT height) {}

void Window::onDestroy()
{
	isRunning = false;
}
