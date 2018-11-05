#include "Bullet.h"
#include "Game.h"
#include <tchar.h>
#include <sstream>

Bullet::Bullet(IDirect3DDevice9* pD3DDevice_,
			   D3DXVECTOR3 position_,
			   D3DXVECTOR3 lookDirNormalized_,
			   D3DXVECTOR3 upAxis_)
	: pD3DDevice(pD3DDevice_),
	  position(position_),
	  previousPosition(position_),
	  lookDirNormalized(lookDirNormalized_),
	  upAxis(upAxis_),
	  originPosition(position_),
	  gravityAxis(0.0f, -10.0f, 0.0f)
{
}

void Bullet::render() const
{
	D3DXMATRIXA16 matWorld, matTransl, matScale;
	D3DXMatrixTranslation(&matTransl, position.x, position.y, position.z);
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	matWorld = matScale * matTransl;
	pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	pD3DDevice->SetTexture(0, Game::getInstance()->loader->pTextureBullet);

	for (DWORD i = 0; i < Game::getInstance()->loader->bulletNumMaterials; ++i)
	{
		Game::getInstance()->loader->bulletMesh->DrawSubset(i);
	}
}

void Bullet::tick(const float deltaTime)
{
	move(deltaTime);
}

void Bullet::move(const float deltaTime)
{
	if (position.y <= 0.0f) return;

	time += deltaTime;

	D3DXVECTOR3 dx = lookDirNormalized * energy * time;
	dx.y = 0.0f;

	D3DXVECTOR3 dy = lookDirNormalized * energy * time + 0.5f * gravityAxis * time * time;
	dy.z = 0.0f;
	dy.x = 0.0f;

	position = originPosition + dx + dy;
	energy = std::fmax(0.0f, energy - 0.02f);

	if (Game::getInstance()->scene->isBirdHit(previousPosition, position))
	{
		Game::getInstance()->counterOfDeadBirds++;
		Game::getInstance()->scene->spawnBird();

#if _DEBUG
		std::stringstream sss;
		sss << "Bullet position x = " << position.x << " y = " << position.y << " Bird hit!!! " << std::endl;
		OutputDebugStringA(sss.str().c_str());
#endif
	}
	previousPosition = position;
}
