#pragma once

#include <d3dx9.h>

class Mouse
{
public:
	Mouse();
	~Mouse() = default;

	D3DXVECTOR2 calculateDelta();

private:
	void updateCursorPos();

	D3DXVECTOR2 centerPos;
	D3DXVECTOR2 deltaPos;
	const float mouseSensitivity = 10.0f;
};
