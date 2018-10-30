#pragma once
#include "Collision.h"
#include "DecisionPoint.h"
#include "Collision.h"
#include <vector>
#include <memory>

class Bird : public Collision
{
public:
	Bird(
		IDirect3DDevice9 *pD3DDevice_,
		D3DXVECTOR3 position_,
		D3DXVECTOR3 lookAt_,
		std::vector<std::shared_ptr<DecisionPoint>> &decisionPointsContainer);
	~Bird();

	void render();
	void tick(float deltaTime);
	CollisionBox getCollisionBox() override;

private:
	void move(float step);
	void turn(float deltaTime);
	void turnLeft(float deltaTime);
	void turnRight(float deltaTime);
	void teleportToDecisionPoint(std::shared_ptr<DecisionPoint> dp);
	std::shared_ptr<DecisionPoint> getAIDecisionPoint();

	IDirect3DDevice9 *pD3DDevice = nullptr;
	ID3DXMesh *ppMesh = nullptr;
	IDirect3DTexture9 *pTextureBird = nullptr;
	DWORD numMaterials;
	D3DXVECTOR3 position;
	D3DXVECTOR3 lookAt;
	D3DXVECTOR3 upAxis;
	D3DXVECTOR3 lookDirNormalized;
	float speed = 1.0f;
	float angleSpeed = 1.0f;
	float linearSpeed = 3.5f;
	bool wasTeleported = true;
	MoveDecision currentMove = MoveDecision::FORWARD;
	std::vector<std::shared_ptr<DecisionPoint>> decisionPointsContainer;
};
