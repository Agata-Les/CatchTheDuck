#include "Player.h"
#include "Game.h"

Player::Player() : position(0.0f, eyePosition, 0.0f), lookAt(1.0f, eyePosition, 0.0f), upAxis(0.0f, 1.0f, 0.0f)
{
	lookDirNormalized = lookAt - position;
	D3DXVec3Normalize(&lookDirNormalized, &lookDirNormalized);
}

void Player::move(float deltaTime)
{
	const float step = velocity * deltaTime;

	D3DXVECTOR3 positionXZ(position.x, eyePosition, position.z);
	D3DXVECTOR3 lookAtXZ(lookAt.x, eyePosition, lookAt.z);
	D3DXVECTOR3 directionXZ = lookAtXZ - positionXZ;
	D3DXVec3Normalize(&directionXZ, &directionXZ);

	if(Game::getInstance()->scene->isCollision(position + directionXZ * step)) return;

	position = position + directionXZ * step;
	lookAt = lookAt + directionXZ * step;

	lookDirNormalized = lookAt - position;
	D3DXVec3Normalize(&lookDirNormalized, &lookDirNormalized);
}

void Player::moveSideway(float deltaTime)
{ 
	float step = velocity * deltaTime;

	D3DXVECTOR3 positionXZ(position.x, eyePosition, position.z);
	D3DXVECTOR3 lookAtXZ(lookAt.x, eyePosition, lookAt.z);
	D3DXVECTOR3 directionXZ = lookAtXZ - positionXZ;
	D3DXVec3Normalize(&directionXZ, &directionXZ);
	D3DXVec3Cross(&directionXZ, &directionXZ, &upAxis);

	if (Game::getInstance()->scene->isCollision(position + directionXZ * step)) return;

	position = position + directionXZ * step;
	lookAt = lookAt + directionXZ * step;

	lookDirNormalized = lookAt - position;
	D3DXVec3Normalize(&lookDirNormalized, &lookDirNormalized);
}
void Player::turn(D3DXVECTOR2 delta)
{
	D3DXMATRIX matRotation;

	D3DXMatrixRotationAxis(&matRotation, &upAxis, D3DXToRadian(delta.x));
	D3DXVec3TransformCoord(&lookDirNormalized, &lookDirNormalized, &matRotation);

	D3DXVECTOR3 positionXZ(position.x, eyePosition, position.z);
	D3DXVECTOR3 lookAtXZ(lookAt.x, eyePosition, lookAt.z);
	D3DXVECTOR3 directionXZ = lookAtXZ - positionXZ;
	D3DXVec3Normalize(&directionXZ, &directionXZ);
	D3DXVec3Cross(&directionXZ, &directionXZ, &upAxis);

	D3DXMatrixRotationAxis(&matRotation, &directionXZ, D3DXToRadian(-delta.y));
	D3DXVec3TransformCoord(&lookDirNormalized, &lookDirNormalized, &matRotation);

	lookAt = position + lookDirNormalized;
	lookDirNormalized = lookAt - position;
	D3DXVec3Normalize(&lookDirNormalized, &lookDirNormalized);
}
