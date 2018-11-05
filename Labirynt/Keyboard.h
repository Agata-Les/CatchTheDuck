#pragma once

#include <map>

enum KeyCode
{
	ESC = 27,
	A = 65,
	D = 68,
	S = 83,
	W = 87,
};

class Keyboard
{
public:
	void tick(const float deltaTime);
	bool getKeyState(const KeyCode keyCode);
	void setKeyState(const KeyCode keyCode, const bool newState);

private:
	std::map<KeyCode, bool> state;
};
