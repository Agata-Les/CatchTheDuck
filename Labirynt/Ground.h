#pragma once
#include <d3d9.h>

class Ground
{
public:
	Ground(IDirect3DDevice9 *pD3DDevice, float groundSize);
	~Ground();

	void render();
	
private:
	void create(float groundSizeXZ);

	IDirect3DDevice9 *pD3DDevice = nullptr;
	IDirect3DVertexBuffer9 *pVBground = nullptr;
	IDirect3DTexture9 *pTextureGrass = nullptr;
	
	const unsigned int numVertexGround;
};
