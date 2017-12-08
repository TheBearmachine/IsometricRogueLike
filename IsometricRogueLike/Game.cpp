#include "Game.h"
#include <SFML/System/Clock.hpp>
#include "IsometricConversion.h"
#include "Clickable.h"

static const char* APP_TITLE = "Isometrica";

Game::Game() :
	mWindow(sf::VideoMode(640, 480), APP_TITLE),
	mGameStateSimulation(this, &mCurrentState),
	mGameStateMenu(this, &mCurrentState)
{

}

Game::~Game()
{

}

void Game::run()
{
	initialize();

	sf::Clock clock;
	while (mWindow.isOpen() && mCurrentState)
	{
		sf::Time dt = clock.restart();
		handleEvents();

		mCurrentState->update(dt);

		mWindow.clear();
		mCurrentState->drawPrep(&mDrawingManager);
		mDrawingManager.draw(&mWindow);
		mWindow.display();
	}
}

void Game::handleEvents()
{
	sf::Event currEvent;
	while (mWindow.pollEvent(currEvent))
	{
		mEventManager.notify(currEvent, &mWindow);
	}
}

void Game::initialize()
{
	Clickable::setup(&mEventManager, &mWindow);
	Window::setup(&mWindow);

	mGameStateSimulation.initalize(&mWindow, &mEventManager);
	mGameStateMenu.initalize(&mWindow, &mEventManager);

	mGameStateMenu.setGameStates(&mGameStateSimulation);
	mGameStateSimulation.setGameStates(&mGameStateMenu);

	mCurrentState = &mGameStateMenu;
}
