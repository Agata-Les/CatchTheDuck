#pragma once

#include "Window.h"
#include "GraphicDevice.h"
#include "Scene.h"
#include "Player.h"
#include "GameTime.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Logger.h"
#include "Loader.h"

#include <memory>

class Game
{
public:
	~Game() = default;

	static Game* getInstance();

	void init(HINSTANCE hInstance);
	MSG loop() const;
	void keyDown(const WPARAM keyNumber) const;
	void keyUp(const WPARAM keyNumber) const;
	void mouseLeftClick() const;

	std::unique_ptr<Window> window;
	std::unique_ptr<GraphicDevice> graphicDev;
	std::unique_ptr<Scene> scene;
	std::unique_ptr<GameTime> gameTime;
	std::unique_ptr<Mouse> mouse;
	std::unique_ptr<Keyboard> keyboard;
	std::unique_ptr<Player> player;
	std::unique_ptr<Logger> logger;
	std::shared_ptr<Loader> loader;

	unsigned short int counterOfDeadBirds = 0;
	
private:
	Game() = default;
	static Game* instance;
};
