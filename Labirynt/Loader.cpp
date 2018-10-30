#include "Loader.h"
#include "Macros.h"
#include <tchar.h>

std::shared_ptr<Loader> Loader::instance = nullptr;

Loader::~Loader()
{
	SAFE_RELEASE(bulletMesh);
	SAFE_RELEASE(pTextureBullet);
	instance = nullptr;
}

std::shared_ptr<Loader> Loader::getInstance()
{
	if (!instance) instance.reset(new Loader());
	return instance;
}

void Loader::load(IDirect3DDevice9 *pD3DDevice)
{
	D3DXCreateTextureFromFile(pD3DDevice, _T("Resources/bullet.jpg"), &pTextureBullet);
	D3DXLoadMeshFromXW(_T("Resources/unitsphere.X"), D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, NULL, NULL, &bulletNumMaterials, &bulletMesh);
}
