#include "Game.h"
#include <SFML/System/Clock.hpp>
#include "IsometricConversion.h"

static const char* APP_TITLE = "Isometrica";

Game::Game() :
	mWindow(sf::VideoMode(640, 480), APP_TITLE),
	mGameStateSimulation(this, mCurrentState),
	mGameStateMenu(this, mCurrentState)
{
	mGameStateSimulation.initalize(&mWindow, &mEventManager);
	mGameStateMenu.initalize(&mWindow, &mEventManager);
	mCurrentState = &mGameStateMenu;
}

Game::~Game()
{

}

void Game::run()
{
	sf::Clock clock;
	while (mWindow.isOpen() && mCurrentState)
	{
		sf::Time dt = clock.restart();
		handleEvents();
		mCurrentState->update(dt);
		mWindow.clear();
		mCurrentState->draw(&mWindow);
		mWindow.display();
	}
}

void Game::handleEvents()
{
	sf::Event currEvent;
	while (mWindow.pollEvent(currEvent))
	{
		mEventManager.notify(currEvent);
	}
}
