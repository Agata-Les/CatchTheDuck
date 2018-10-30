#include "Mouse.h"
#include <Windows.h>

Mouse::Mouse() : centerPos(800.0f, 600.0f)
{
	updateCursorPos();
}

D3DXVECTOR2 Mouse::calculateDelta()
{
	POINT point;
	GetCursorPos(&point);

	D3DXVECTOR2 delta;
	delta.x = point.x - centerPos.x;
	delta.y = point.y - centerPos.y;

	updateCursorPos();

	return delta / mouseSensitivity;
}

void Mouse::updateCursorPos()
{
	SetCursorPos((int)centerPos.x, (int)centerPos.y);
}
