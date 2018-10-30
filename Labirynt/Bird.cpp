#include "Bird.h"
#include "Game.h"
#include "Macros.h"
#include <tchar.h>
#include <sstream>

Bird::Bird(IDirect3DDevice9 *pD3DDevice_, D3DXVECTOR3 position_, D3DXVECTOR3 lookAt_, std::vector<std::shared_ptr<DecisionPoint>> &decisionPointsContainer_) :
	pD3DDevice(pD3DDevice_), position(position_), lookAt(lookAt_), upAxis(0.0f, 1.0f, 0.0f), decisionPointsContainer(decisionPointsContainer_)
{
	D3DXCreateTextureFromFile(pD3DDevice, _T("Resources/feathers.png"), &pTextureBird);
	D3DXLoadMeshFromXW(_T("Resources/unitsphere.X"), D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, NULL, NULL, &numMaterials, &ppMesh);

	lookDirNormalized = lookAt - position;
	D3DXVec3Normalize(&lookDirNormalized, &lookDirNormalized);
}

Bird::~Bird()
{
	SAFE_RELEASE(ppMesh);
	SAFE_RELEASE(pTextureBird);
}

void Bird::render()
{
	D3DXMATRIXA16 matWorld, matTransl, matScale;
	D3DXMatrixTranslation(&matTransl, position.x, position.y, position.z);
	D3DXMatrixScaling(&matScale, 0.2f, 0.2f, 0.2f);
	matWorld = matScale * matTransl;
	pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	pD3DDevice->SetTexture(0, pTextureBird);

	for (DWORD i = 0; i < numMaterials; ++i)
	{
		ppMesh->DrawSubset(i);
	}
}

void Bird::tick(float deltaTime)
{
	std::shared_ptr<DecisionPoint> dp = getAIDecisionPoint();

	if (dp && !wasTeleported)
	{
		currentMove = dp->getRandomMove();
		teleportToDecisionPoint(dp);
		wasTeleported = true;
	}

	if (!dp) 
	{
		wasTeleported = false;
	}

	if (currentMove == MoveDecision::FORWARD) move(deltaTime * speed);
	else if (currentMove == MoveDecision::LEFT) turnLeft(deltaTime * speed);
	else if (currentMove == MoveDecision::RIGHT) turnRight(deltaTime * speed);
}

CollisionBox Bird::getCollisionBox()
{
	const float r = 0.1f;
	D3DXVECTOR3 DLF(position.x - r, position.y - r, position.z - r);
	D3DXVECTOR3 DRF(position.x + r, position.y - r, position.z - r);
	D3DXVECTOR3 DLB(position.x - r, position.y - r, position.z + r);
	D3DXVECTOR3 ULF(position.x - r, position.y + r, position.z - r);

	return CollisionBox(ULF, DLF, DLB, DRF);
}

void Bird::move(float deltaTime)
{
	position += lookDirNormalized * linearSpeed * deltaTime;
	lookAt += lookDirNormalized * linearSpeed * deltaTime;
}

void Bird::turn(float deltaTime)
{
	const float alpha = angleSpeed * deltaTime;

	D3DXMATRIX matRotation;
	D3DXMatrixRotationAxis(&matRotation, &upAxis, alpha);
	D3DXVec3TransformCoord(&lookDirNormalized, &lookDirNormalized, &matRotation);

	lookAt = position + lookDirNormalized;
}

void Bird::turnLeft(float deltaTime)
{
	angleSpeed = -1.0f;

	turn(deltaTime);
	move(deltaTime);
}

void Bird::turnRight(float deltaTime)
{
	angleSpeed = 1.0f;

	turn(deltaTime);
	move(deltaTime);
}

void Bird::teleportToDecisionPoint(std::shared_ptr<DecisionPoint> dp)
{
	position.x = dp->decisionPointX;
	position.z = dp->decisionPointZ;

	lookDirNormalized.x = std::round(lookDirNormalized.x);
	lookDirNormalized.y = std::round(lookDirNormalized.y);
	lookDirNormalized.z = std::round(lookDirNormalized.z);
	D3DXVec3Normalize(&lookDirNormalized, &lookDirNormalized);

	lookAt = position + lookDirNormalized;
}

std::shared_ptr<DecisionPoint> Bird::getAIDecisionPoint()
{
	for (auto& dp : decisionPointsContainer)
	{
		if (dp->isInDecisionPoint(position)) return dp;
	}
	return nullptr;
}
