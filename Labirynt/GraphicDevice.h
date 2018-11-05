#pragma once

#include <d3d9.h>

class GraphicDevice
{
public:
	GraphicDevice(HWND hWnd);
	~GraphicDevice();

	void render() const;

	IDirect3DDevice9* pD3DDevice = nullptr;

private:
	void initialize();
	void create(HWND hWnd);

	IDirect3D9* pD3D = nullptr;
};
