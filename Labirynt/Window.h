#pragma once

#include <Windows.h>
#include <tchar.h>

class Window
{
public:
	Window(HINSTANCE hInstance);
	~Window();

	void show() const;

	HWND hWnd;

private:
	void registerWindowClass() const;
	void createWindow();

	HINSTANCE hInstance;
	const LPCWSTR windowNameClass = _T("CatchTheDuckWndClass");
	const LPCWSTR windowTitle = _T("Catch the duck");
};
