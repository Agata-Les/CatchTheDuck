#include "Collision.h"

bool Collision::isColliding(const D3DXVECTOR3 &point)
{
	CollisionBox cBox = getCollisionBox();

	D3DXVECTOR3 i = cBox.DLB - cBox.DLF;
	D3DXVECTOR3 j = cBox.DRF - cBox.DLF;
	D3DXVECTOR3 k = cBox.ULF - cBox.DLF;
	D3DXVECTOR3 v = point - cBox.DLF;

	if (0.0f < D3DXVec3Dot(&v, &i) && D3DXVec3Dot(&v, &i) < D3DXVec3Dot(&i, &i)
		&&
		0.0f < D3DXVec3Dot(&v, &j) && D3DXVec3Dot(&v, &j) < D3DXVec3Dot(&j, &j)
		&&
		0.0f < D3DXVec3Dot(&v, &k) && D3DXVec3Dot(&v, &k) < D3DXVec3Dot(&k, &k)) return true;

	return false;
}
