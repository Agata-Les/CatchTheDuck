#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class Bullet
{
public:
	Bullet(IDirect3DDevice9* pD3DDevice_,
		   D3DXVECTOR3 position_,
		   D3DXVECTOR3 lookDirNormalized_,
		   D3DXVECTOR3 upAxis_);
	~Bullet() = default;

	void render() const;
	void tick(const float deltaTime);

private:
	void move(const float deltaTime);

	IDirect3DDevice9 *pD3DDevice = nullptr;

	D3DXVECTOR3 position;
	D3DXVECTOR3 previousPosition;
	D3DXVECTOR3 lookDirNormalized;
	D3DXVECTOR3 upAxis;
	const D3DXVECTOR3 originPosition;
	const D3DXVECTOR3 gravityAxis;
	float energy = 100.0f;
	float time = 0.0f;
};
