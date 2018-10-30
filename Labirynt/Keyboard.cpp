#include "Keyboard.h"
#include "Game.h"

void Keyboard::tick(float deltaTime)
{
	if (getKeyState(KeyCode::W)) Game::getInstance()->player->move(deltaTime);
	if (getKeyState(KeyCode::S)) Game::getInstance()->player->move(-deltaTime);
	if (getKeyState(KeyCode::D)) Game::getInstance()->player->moveSideway(-deltaTime);
	if (getKeyState(KeyCode::A)) Game::getInstance()->player->moveSideway(deltaTime);
}

bool Keyboard::getKeyState(KeyCode keyCode)
{
	auto lookUpKey = state.find(keyCode);
	if (lookUpKey == state.end()) return false;

	return lookUpKey->second;
}

void Keyboard::setKeyState(KeyCode keyCode, bool newState)
{
	state[keyCode] = newState;
}
