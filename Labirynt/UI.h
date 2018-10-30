#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>

class UI
{
public:
	UI(IDirect3DDevice9 * pD3DDevice_);
	~UI();

	void render();

private:
	void initialize();

	void drawLine(int p1x, int p1y, int p2x, int p2y, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void drawCross(int centerX, int centerY, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void drawRectangle(int p1x, int p1y, int p2x, int p2y, D3DCOLOR color = D3DCOLOR_XRGB(0, 0, 0));
	void drawText(std::wstring text, int x, int y, int width, int height, ID3DXFont *pFont, DWORD color);
	void drawTextTIME();

	IDirect3DDevice9 * pD3DDevice = nullptr;
	ID3DXLine *pLine = nullptr;
	ID3DXFont *pFontWin = nullptr;
	ID3DXFont *pFontCatch = nullptr;
	ID3DXFont *pFontTime = nullptr;
};
