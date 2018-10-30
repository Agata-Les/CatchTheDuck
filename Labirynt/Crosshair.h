#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class Crosshair
{
public:
	Crosshair(IDirect3DDevice9 *pD3DDevice_);
	~Crosshair();

	void render();

private:
	void initialize();
	void drawLine(float p1x, float p1y, float p2x, float p2y);

	D3DXVECTOR2 centerPoint;
	IDirect3DDevice9 *pD3DDevice = nullptr;
	ID3DXLine *pLine = nullptr;
};
