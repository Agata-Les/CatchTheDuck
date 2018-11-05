#include "Keyboard.h"
#include "Game.h"

void Keyboard::tick(const float deltaTime)
{
	if (getKeyState(KeyCode::W)) Game::getInstance()->player->move(deltaTime);
	if (getKeyState(KeyCode::S)) Game::getInstance()->player->move(-deltaTime);
	if (getKeyState(KeyCode::D)) Game::getInstance()->player->moveSideway(-deltaTime);
	if (getKeyState(KeyCode::A)) Game::getInstance()->player->moveSideway(deltaTime);
}

bool Keyboard::getKeyState(const KeyCode keyCode)
{
	const auto lookUpKey = state.find(keyCode);
	if (lookUpKey == state.end()) return false;

	return lookUpKey->second;
}

void Keyboard::setKeyState(const KeyCode keyCode, const bool newState)
{
	state[keyCode] = newState;
}
