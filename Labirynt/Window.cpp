#include "Window.h"
#include "Game.h"

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
		Game::getInstance()->keyDown(wParam);
		return 0;

	case WM_KEYUP:
		Game::getInstance()->keyUp(wParam);
		return 0;

	case WM_LBUTTONDOWN:
		Game::getInstance()->mouseLeftClick();
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

Window::Window(HINSTANCE hInstance_) : hInstance(hInstance_)
{
	registerWindowClass();
	createWindow();
}

Window::~Window()
{
	UnregisterClass(windowNameClass, hInstance);
}

void Window::registerWindowClass() const
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.lpszClassName = windowNameClass;

	RegisterClassEx(&wc);
}

void Window::createWindow()
{
	hWnd = CreateWindow(
		windowNameClass,
		windowTitle,
		WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		1600, 1200,
		NULL, NULL,
		hInstance,
		NULL);
}

void Window::show() const
{
	ShowCursor(false);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
}
