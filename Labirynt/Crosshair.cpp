#include "Crosshair.h"
#include "Macros.h"

Crosshair::Crosshair(IDirect3DDevice9 * pD3DDevice_) : pD3DDevice(pD3DDevice_)
{
	initialize();
}

Crosshair::~Crosshair()
{
	SAFE_RELEASE(pLine);
}

void Crosshair::render() const
{
	drawLine(centerPoint.x + 15.0f, centerPoint.y + 15.0f, centerPoint.x + 3.0f, centerPoint.y + 3.0f);
	drawLine(centerPoint.x - 15.0f, centerPoint.y + 15.0f, centerPoint.x - 3.0f, centerPoint.y + 3.0f);
	drawLine(centerPoint.x + 15.0f, centerPoint.y - 15.0f, centerPoint.x + 3.0f, centerPoint.y - 3.0f);
	drawLine(centerPoint.x - 15.0f, centerPoint.y - 15.0f, centerPoint.x - 3.0f, centerPoint.y - 3.0f);
}

void Crosshair::initialize()
{
	D3DVIEWPORT9 viewPort;
	pD3DDevice->GetViewport(&viewPort);

	centerPoint.x = viewPort.Width / 2.0f;
	centerPoint.y = viewPort.Height / 2.0f;

	D3DXCreateLine(pD3DDevice, &pLine);
	pLine->SetWidth(3.0f);
	pLine->SetAntialias(false);
	pLine->SetGLLines(true);
}

void Crosshair::drawLine(const float p1x, const float p1y, const float p2x, const float p2y) const
{
	const D3DCOLOR color = D3DCOLOR_XRGB(255, 0, 0);
	D3DXVECTOR2 vLine[2];

	vLine[0].x = p1x;
	vLine[0].y = p1y;
	vLine[1].x = p2x;
	vLine[1].y = p2y;

	pLine->Begin();
	pLine->Draw(vLine, 2, color);
	pLine->End();
}
