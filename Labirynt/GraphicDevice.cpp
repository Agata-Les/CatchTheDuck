#include "GraphicDevice.h"
#include "Vertex.h"
#include "Macros.h"
#include "Game.h"

#include <d3dx9.h>

GraphicDevice::GraphicDevice(HWND hWnd)
{
	initialize();
	create(hWnd);
}

GraphicDevice::~GraphicDevice()
{
	SAFE_RELEASE(pD3DDevice);
	SAFE_RELEASE(pD3D);
}

void GraphicDevice::render() const
{
	pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(50, 40, 30), 1.0f, 0);
	pD3DDevice->BeginScene();
	pD3DDevice->SetFVF(FVF_VERTEX);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 3.0f, 1600.0f / 1200.0f, 0.1f, 1000.0f);
	pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	Game::getInstance()->scene->render();

	pD3DDevice->EndScene();
	pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void GraphicDevice::initialize()
{
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
}

void GraphicDevice::create(HWND hWnd)
{
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, 
		hWnd, 
		D3DCREATE_HARDWARE_VERTEXPROCESSING, 
		&d3dpp,
		&pD3DDevice);
}
