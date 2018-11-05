#include "Building.h"
#include "Macros.h"

#include <tchar.h>

Building::Building(IDirect3DDevice9* pD3DDevice_, D3DXVECTOR2 position_, const float height_)
	: pD3DDevice(pD3DDevice_), position(position_), height(height_)
{
	D3DXCreateTextureFromFile(pD3DDevice, _T("Resources/building.jpg"), &pTextureBuilding);
	D3DXLoadMeshFromXW(_T("Resources/unitbox.X"), D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, NULL, NULL, &numMaterials, &pMesh);
}

Building::~Building()
{
	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pTextureBuilding);
}

void Building::render() const
{
	D3DXMATRIXA16 matWorld, matScale, matTransl;
	D3DXMatrixTranslation(&matTransl, position.x, 0.5f * height, position.y);
	D3DXMatrixScaling(&matScale, buildingWidth, height, buildingWidth);
	matWorld =  matScale * matTransl;
	pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	pD3DDevice->SetTexture(0, pTextureBuilding);

	for (DWORD i = 0; i < numMaterials; ++i)
	{
		pMesh->DrawSubset(i);
	}
}

CollisionBox Building::getCollisionBox()
{
	D3DXVECTOR3 DLF( position.x - 0.6f * buildingWidth, 0.0f, position.y - 0.6f * buildingWidth);
	D3DXVECTOR3 DRF( position.x + 0.6f * buildingWidth, 0.0f, position.y - 0.6f * buildingWidth);
	D3DXVECTOR3 DLB( position.x - 0.6f * buildingWidth, 0.0f, position.y + 0.6f * buildingWidth);
	D3DXVECTOR3 ULF( position.x - 0.6f * buildingWidth, height, position.y - 0.6f * buildingWidth);

	return { ULF, DLF, DLB, DRF };
}
