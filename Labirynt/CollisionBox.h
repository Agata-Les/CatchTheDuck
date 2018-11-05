#pragma once

#include <d3dx9.h>

struct CollisionBox
{
	CollisionBox(const D3DXVECTOR3& ULF_,
		const D3DXVECTOR3& DLF_,
		const D3DXVECTOR3& DLB_,
		const D3DXVECTOR3& DRF_) 
	: ULF(ULF_),
	  DLF(DLF_),
	  DLB(DLB_),
	  DRF(DRF_) {}

	D3DXVECTOR3 ULF, DLF, DLB, DRF;
};
