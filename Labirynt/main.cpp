#include "Game.h"
#include <Windows.h>

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, INT)
{
	Game * game = Game::getInstance();
	game->init(hInstance);

	MSG msg = game->loop();

	return msg.wParam;
}
