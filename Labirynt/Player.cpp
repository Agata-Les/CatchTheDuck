#include "Player.h"
#include "Game.h"

Player::Player()
{
	lookDirNormalized = lookAt - position;
	D3DXVec3Normalize(&lookDirNormalized, &lookDirNormalized);
}

void Player::move(const float deltaTime)
{
	const float step = velocity * deltaTime;

	const D3DXVECTOR3 positionXZ(position.x, eyePosition, position.z);
	const D3DXVECTOR3 lookAtXZ(lookAt.x, eyePosition, lookAt.z);
	D3DXVECTOR3 directionXZ = lookAtXZ - positionXZ;
	D3DXVec3Normalize(&directionXZ, &directionXZ);

	if(Game::getInstance()->scene->isCollision(position + directionXZ * step)) return;

	position = position + directionXZ * step;
	lookAt = lookAt + directionXZ * step;

	lookDirNormalized = lookAt - position;
	D3DXVec3Normalize(&lookDirNormalized, &lookDirNormalized);
}

void Player::moveSideway(const float deltaTime)
{ 
	const float step = velocity * deltaTime;

	const D3DXVECTOR3 positionXZ(position.x, eyePosition, position.z);
	const D3DXVECTOR3 lookAtXZ(lookAt.x, eyePosition, lookAt.z);
	D3DXVECTOR3 directionXZ = lookAtXZ - positionXZ;
	D3DXVec3Normalize(&directionXZ, &directionXZ);
	D3DXVec3Cross(&directionXZ, &directionXZ, &upAxis);

	if (Game::getInstance()->scene->isCollision(position + directionXZ * step)) return;

	position = position + directionXZ * step;
	lookAt = lookAt + directionXZ * step;

	lookDirNormalized = lookAt - position;
	D3DXVec3Normalize(&lookDirNormalized, &lookDirNormalized);
}
void Player::turn(const D3DXVECTOR2& delta)
{
	D3DXMATRIX matRotation;

	D3DXMatrixRotationAxis(&matRotation, &upAxis, D3DXToRadian(delta.x));
	D3DXVec3TransformCoord(&lookDirNormalized, &lookDirNormalized, &matRotation);

	const D3DXVECTOR3 positionXZ(position.x, eyePosition, position.z);
	const D3DXVECTOR3 lookAtXZ(lookAt.x, eyePosition, lookAt.z);
	D3DXVECTOR3 directionXZ = lookAtXZ - positionXZ;
	D3DXVec3Normalize(&directionXZ, &directionXZ);
	D3DXVec3Cross(&directionXZ, &directionXZ, &upAxis);

	D3DXMatrixRotationAxis(&matRotation, &directionXZ, D3DXToRadian(-delta.y));
	D3DXVec3TransformCoord(&lookDirNormalized, &lookDirNormalized, &matRotation);

	lookAt = position + lookDirNormalized;
	lookDirNormalized = lookAt - position;
	D3DXVec3Normalize(&lookDirNormalized, &lookDirNormalized);
}
