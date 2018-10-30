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
	void tick(float deltaTime);
	bool getKeyState(KeyCode keyCode);
	void setKeyState(KeyCode keyCode, bool newState);

private:
	std::map<KeyCode, bool> state;
};
