#pragma once

#include <d3d9.h>

class Ground
{
public:
	Ground(IDirect3DDevice9* pD3DDevice, const float groundSize);
	~Ground();

	void render() const;
	
private:
	void create(const float groundSizeXZ) const;

	IDirect3DDevice9* pD3DDevice = nullptr;
	IDirect3DVertexBuffer9* pVBground = nullptr;
	IDirect3DTexture9* pTextureGrass = nullptr;
	
	const unsigned int numVertexGround;
};
