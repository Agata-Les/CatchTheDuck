#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class Crosshair
{
public:
	Crosshair(IDirect3DDevice9* pD3DDevice_);
	~Crosshair();

	void render() const;

private:
	void initialize();
	void drawLine(const float p1x, const float p1y, const float p2x, const float p2y) const;

	D3DXVECTOR2 centerPoint;
	IDirect3DDevice9* pD3DDevice = nullptr;
	ID3DXLine* pLine = nullptr;
};
