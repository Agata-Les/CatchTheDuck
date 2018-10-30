#pragma once

#include "CollisionBox.h"
#include <d3dx9.h>

class Collision
{
public:
	Collision() = default;
	virtual ~Collision() = default;

	bool isColliding(const D3DXVECTOR3 &point);
	virtual CollisionBox getCollisionBox() = 0;
};
