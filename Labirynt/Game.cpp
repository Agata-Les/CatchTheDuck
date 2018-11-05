#include "Game.h"

#include <ctime>

Game* Game::instance = nullptr;

Game* Game::getInstance()
{
	if (instance == nullptr) instance = new Game();
	return instance;
}

void Game::init(HINSTANCE hInstance)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	window = std::make_unique<Window>(hInstance);
	graphicDev = std::make_unique<GraphicDevice>(window->hWnd);
	scene = std::make_unique<Scene>(graphicDev->pD3DDevice);
	player = std::make_unique<Player>();
	gameTime = std::make_unique<GameTime>();
	mouse = std::make_unique<Mouse>();
	keyboard = std::make_unique<Keyboard>();
	logger = std::make_unique<Logger>();
	loader = Loader::getInstance();
	loader->load(graphicDev->pD3DDevice);

	logger->info("Game initialization");
	window->show();
}

MSG Game::loop() const
{
	MSG msg;
	while (true)
	{
		if (!PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			const float elapsedTime = gameTime->calculateElapsedTime();
			if (elapsedTime >= 0.011f)
			{	
				keyboard->tick(elapsedTime);
				scene->tick(elapsedTime);
				player->turn(mouse->calculateDelta());
				graphicDev->render();
				gameTime->update();
			}
			continue;
		}

		if (msg.message == WM_QUIT)
		{
			break;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg;
}

void Game::keyDown(const WPARAM keyNumber) const
{
	if (keyNumber == KeyCode::ESC) PostQuitMessage(0);
	keyboard->setKeyState((KeyCode)keyNumber, true);
}

void Game::keyUp(const WPARAM keyNumber) const
{
	keyboard->setKeyState((KeyCode)keyNumber, false);
}

void Game::mouseLeftClick() const
{
	scene->spawnBullet();
}
