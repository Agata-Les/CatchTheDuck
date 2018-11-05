#pragma once

#include "Collision.h"
#include "DecisionPoint.h"

#include <vector>
#include <memory>

class Bird : public Collision
{
public:
	Bird(IDirect3DDevice9 *pD3DDevice_,
		 D3DXVECTOR3 position_,
		 D3DXVECTOR3 lookAt_,
		 const std::vector<std::shared_ptr<DecisionPoint>> &decisionPointsContainer);
	~Bird();

	void render() const;
	void tick(float deltaTime);
	CollisionBox getCollisionBox() override;

private:
	void move(const float step);
	void turn(const float deltaTime);
	void turnLeft(const float deltaTime);
	void turnRight(const float deltaTime);
	void teleportToDecisionPoint(const std::shared_ptr<DecisionPoint> dp);
	std::shared_ptr<DecisionPoint> getAIDecisionPoint() const;

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
	const std::vector<std::shared_ptr<DecisionPoint>>& decisionPointsContainer;
};
