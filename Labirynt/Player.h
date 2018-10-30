#pragma once
#include <d3dx9.h>

class Player
{
public:
	Player();
	~Player() = default;

	const float eyePosition = 1.0f;
	D3DXVECTOR3 position;
	D3DXVECTOR3 lookAt;
	D3DXVECTOR3 upAxis;
	D3DXVECTOR3 lookDirNormalized;
	
	void move(float deltaTime);
	void moveSideway(float deltaTime);
	void turn(D3DXVECTOR2 delta);

private:
	const float velocity = 10.0f;
};
