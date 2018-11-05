#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include <string>

class UI
{
public:
	UI(IDirect3DDevice9* pD3DDevice_);
	~UI();

	void render() const;

private:
	void initialize();

	void drawLine(const int p1x,
				  const int p1y,
				  const int p2x,
				  const int p2y,
				  const D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) const;
	void drawCross(const int centerX,
				   const int centerY,
				   const D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) const;
	void drawRectangle(const int p1x,
					   const int p1y,
					   const int p2x,
					   const int p2y,
					   const D3DCOLOR color = D3DCOLOR_XRGB(0, 0, 0)) const;
	void drawText(const std::wstring&& text,
				  const int x,
				  const int y,
				  const int width,
				  const int height,
				  ID3DXFont* pFont,
				  const DWORD color) const;
	void drawTextTIME() const;

	IDirect3DDevice9 * pD3DDevice = nullptr;
	ID3DXLine *pLine = nullptr;
	ID3DXFont *pFontWin = nullptr;
	ID3DXFont *pFontCatch = nullptr;
	ID3DXFont *pFontTime = nullptr;
};
