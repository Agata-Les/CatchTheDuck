#pragma once
#include <d3d9.h>

class Skybox
{
public:
	Skybox(IDirect3DDevice9 *pD3DDevice_);
	~Skybox();

	void render();

private:
	void create();

	IDirect3DVertexBuffer9 *pVB = nullptr;
	IDirect3DIndexBuffer9 *pIB = nullptr;
	IDirect3DTexture9 *pTextureSkybox = nullptr;
	IDirect3DDevice9 *pD3DDevice = nullptr;

	const unsigned short int numOfVertices = 16;
	const unsigned short int numOfIndices = 34;
	const float skyBoxWidth = 500.0f;
};
