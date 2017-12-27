#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include "GameState.h"
#include "GameStateSimulation.h"
#include "GameStateMenu.h"
#include "EventManager.h"
#include "DrawingManager.h"
#include "MousePointer.h"

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	void handleEvents();
	void initialize();

	sf::RenderWindow mWindow;
	EventManager mEventManager;
	DrawingManager mDrawingManager;

	MousePointer mMousePointer;

	GameState* mCurrentState;
	GameStateSimulation mGameStateSimulation;
	GameStateMenu mGameStateMenu;
};