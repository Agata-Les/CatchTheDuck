#pragma once

#include <d3dx9.h>

class Mouse
{
public:
	Mouse();
	~Mouse() = default;

	D3DXVECTOR2 calculateDelta() const;

private:
	void updateCursorPos() const;

	const D3DXVECTOR2 centerPos { 800.0f, 600.0f };
	const float mouseSensitivity = 10.0f;
};
