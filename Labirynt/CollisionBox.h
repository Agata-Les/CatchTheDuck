#pragma once
#include <d3dx9.h>

struct CollisionBox
{
	CollisionBox(D3DXVECTOR3 &ULF_, D3DXVECTOR3 &ULB_, D3DXVECTOR3 &URF_, D3DXVECTOR3 &URB_,
			     D3DXVECTOR3 &DLF_, D3DXVECTOR3 &DLB_, D3DXVECTOR3 &DRF_, D3DXVECTOR3 &DRB_) :
		         ULF(ULF_), ULB(ULB_), URF(URF_), URB(URB_), DLF(DLF_), DLB(DLB_), DRF(DRF_), DRB(DRB_) {}

	CollisionBox(D3DXVECTOR3 &ULF_, D3DXVECTOR3 &DLF_, D3DXVECTOR3 &DLB_, D3DXVECTOR3 &DRF_) :
		         ULF(ULF_),  DLF(DLF_), DLB(DLB_), DRF(DRF_) {}

	D3DXVECTOR3 ULF, ULB, URF, URB;
	D3DXVECTOR3 DLF, DLB, DRF, DRB;
};

