#pragma once
#include "Scene.h"
#include <d3d9.h>
#include <memory>

class GraphicDevice
{
public:
	GraphicDevice(HWND hWnd);
	~GraphicDevice();

	void render();

	IDirect3DDevice9 *pD3DDevice = nullptr;

private:
	void initialize();
	void create(HWND hWnd);

	IDirect3D9 *pD3D = nullptr;
};
