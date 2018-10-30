#pragma once

#include "Collision.h"
#include <d3d9.h>
#include <d3dx9.h>

class Building : public Collision
{
public:
	Building(IDirect3DDevice9 *pD3DDevice_, D3DXVECTOR2 position_, float height_);
	~Building();

	void render();
	CollisionBox getCollisionBox() override;

private:
	IDirect3DDevice9 *pD3DDevice = nullptr;
	ID3DXMesh *pMesh = nullptr;
	IDirect3DTexture9 *pTextureBuilding = nullptr;
	DWORD numMaterials = 0;
	D3DXVECTOR3 position;
	const float buildingWidth = 4.0f;
	float height = 0.0f;
};
