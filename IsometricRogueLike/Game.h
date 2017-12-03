#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include "GameState.h"
#include "GameStateSimulation.h"
#include "GameStateMenu.h"
#include "EventManager.h"

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	void handleEvents();

	sf::RenderWindow mWindow;
	EventManager mEventManager;

	GameState* mCurrentState;
	GameStateSimulation mGameStateSimulation;
	GameStateMenu mGameStateMenu;
};