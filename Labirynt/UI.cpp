#include "UI.h"
#include "Game.h"
#include "Macros.h"
#include <d3dx9.h>
#include <tchar.h>
#include <sstream>

UI::UI(IDirect3DDevice9 * pD3DDevice_) : pD3DDevice(pD3DDevice_)
{
	initialize();
}

UI::~UI()
{
	SAFE_RELEASE(pLine);
	SAFE_RELEASE(pFontWin);
	SAFE_RELEASE(pFontCatch);
	SAFE_RELEASE(pFontTime);
}

void UI::render()
{
	const unsigned short int numberOfBirdsHit = Game::getInstance()->counterOfDeadBirds;

	drawRectangle(10, 10, 210, 60);

	drawLine(60, 60, 60, 10);
	drawLine(110, 60, 110, 10);
	drawLine(160, 60, 160, 10);

	drawRectangle(20, 20, 50, 50, D3DCOLOR_XRGB(255, 255, 0));
	drawRectangle(70, 20, 100, 50, D3DCOLOR_XRGB(255, 255, 0));
	drawRectangle(120, 20, 150, 50, D3DCOLOR_XRGB(255, 255, 0));
	drawRectangle(170, 20, 200, 50, D3DCOLOR_XRGB(255, 255, 0));

	drawText(_T("Catch the bird"), 25, 70, 100, 100, pFontCatch, D3DCOLOR_XRGB(255, 255, 0));

	if (numberOfBirdsHit > 0) drawCross(35, 35, D3DCOLOR_XRGB(255, 0, 0));
	if (numberOfBirdsHit > 1) drawCross(85, 35, D3DCOLOR_XRGB(255, 0, 0));
	if (numberOfBirdsHit > 2) drawCross(135, 35, D3DCOLOR_XRGB(255, 0, 0));
	if (numberOfBirdsHit > 3)
	{
		drawCross(185, 35, D3DCOLOR_XRGB(255, 0, 0));

		D3DVIEWPORT9 viewPort;
		pD3DDevice->GetViewport(&viewPort);
		int centerPointX = viewPort.Width / 2;
		int centerPointY = viewPort.Height / 2;

		drawText(_T("You win"), centerPointX - 150, centerPointY - 150, 100, 100, pFontWin, D3DCOLOR_XRGB(255, 0, 0));
		drawTextTIME();
	}
}

void UI::initialize()
{
	D3DXCreateLine(pD3DDevice, &pLine);
	pLine->SetWidth(4.0f);
	pLine->SetAntialias(false);
	pLine->SetGLLines(true);

	D3DXCreateFont(
		pD3DDevice,
		100,
		0,
		FW_BOLD,
		1,
		false,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		_T("Arial"),
		&pFontWin);

	D3DXCreateFont(
		pD3DDevice,
		30,
		0,
		FW_BOLD,
		1,
		false,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		_T("Arial"),
		&pFontCatch);

	D3DXCreateFont(
		pD3DDevice,
		30,
		0,
		FW_BOLD,
		1,
		false,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		_T("Arial"),
		&pFontTime);
}

void UI::drawLine(int p1x, int p1y, int p2x, int p2y, D3DCOLOR color)
{
	D3DXVECTOR2 vLine[2];

	vLine[0].x = static_cast<float>(p1x);
	vLine[0].y = static_cast<float>(p1y);
	vLine[1].x = static_cast<float>(p2x);
	vLine[1].y = static_cast<float>(p2y);

	pLine->Begin();
	pLine->Draw(vLine, 2, color);
	pLine->End();
}

void UI::drawCross(int centerX, int centerY, D3DCOLOR color)
{
	drawLine(centerX - 25, centerY - 25, centerX + 25, centerY + 25, color);
	drawLine(centerX - 25, centerY + 25, centerX + 25, centerY - 25, color);
}

void UI::drawRectangle(int p1x, int p1y, int p2x, int p2y, D3DCOLOR color)
{
	D3DRECT rect{ p1x, p1y, p2x, p2y };
	pD3DDevice->Clear(1, &rect, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0);

	drawLine(p1x, p1y, p1x, p2y);
	drawLine(p1x, p2y, p2x, p2y);
	drawLine(p2x, p2y, p2x, p1y);
	drawLine(p2x, p1y, p1x, p1y);
}

void UI::drawText(std::wstring text, int x, int y, int width, int height, ID3DXFont *pFont, DWORD color)
{
	RECT fontRect;
	SetRect(&fontRect, x, y, width, height);

	pFont->DrawText(
		NULL,
		text.c_str(),
		-1,
		&fontRect,
		DT_LEFT | DT_NOCLIP,
		color);
}

void UI::drawTextTIME()
{
	static float totalGameTime = Game::getInstance()->gameTime->getTotalGameTime();

	D3DVIEWPORT9 viewPort;
	pD3DDevice->GetViewport(&viewPort);
	int centerPointX = viewPort.Width / 2;
	int centerPointY = viewPort.Height / 2;

	std::wstringstream wss;
	wss.precision(5);
	wss << "Your time: " << totalGameTime << " s";

	drawText(wss.str(), centerPointX - 300, centerPointY + 50, 100, 100, pFontWin, D3DCOLOR_XRGB(255, 0, 0));
}
