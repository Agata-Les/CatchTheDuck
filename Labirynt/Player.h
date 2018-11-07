#pragma once

#include <d3dx9.h>

class Player
{
public:
	Player();
	~Player() = default;

	const float eyePosition = 1.0f;
	D3DXVECTOR3 position { 0.0f, eyePosition, 0.0f };
	D3DXVECTOR3 lookAt { 1.0f, eyePosition, 0.0f };
	const D3DXVECTOR3 upAxis { 0.0f, 1.0f, 0.0f };
	D3DXVECTOR3 lookDirNormalized;
	
	void move(const float deltaTime);
	void moveSideway(const float deltaTime);
	void turn(const D3DXVECTOR2& delta);

private:
	const float velocity = 10.0f;
};
