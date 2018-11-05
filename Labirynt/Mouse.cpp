#include "Mouse.h"

#include <Windows.h>

Mouse::Mouse()
{
	updateCursorPos();
}

D3DXVECTOR2 Mouse::calculateDelta() const
{
	POINT point;
	GetCursorPos(&point);

	D3DXVECTOR2 delta;
	delta.x = point.x - centerPos.x;
	delta.y = point.y - centerPos.y;

	updateCursorPos();

	return delta / mouseSensitivity;
}

void Mouse::updateCursorPos() const
{
	SetCursorPos((int)centerPos.x, (int)centerPos.y);
}
