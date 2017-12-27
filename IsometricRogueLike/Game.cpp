#include "Game.h"
#include "IsometricConversion.h"
#include "Clickable.h"
#include "SimulationController.h"
#include "Constants.h"
#include "ItemDatabase.h"
#include "ItemManager.h"
#include <string>
#include <SFML/System/Clock.hpp>

static const char* APP_TITLE = "Isometrica";
static const std::string MOUSEPOINTER_TEX = Constants::Filepaths::ImagesFolder + "MousePointer.png";

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
		mMousePointer.drawPrep(&mDrawingManager);

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
	Clickable::setup(&mWindow);
	EventObserver::setup(&mEventManager);
	MousePointer::setup(&mWindow);
	Window::setup(&mWindow);
	WindowManager::setup(&mEventManager);
	ItemManager::setMousePointer(&mMousePointer);
	SimulationController::setup(&mWindow, &mEventManager, &mMousePointer);
	ItemDatabase::getInstance();

	mGameStateSimulation.initalize(&mWindow, &mEventManager);
	mGameStateMenu.initalize(&mWindow, &mEventManager);

	mGameStateMenu.setGameStates(&mGameStateSimulation);
	mGameStateSimulation.setGameStates(&mGameStateMenu);

	mCurrentState = &mGameStateMenu;

	mMousePointer.setSprite(MOUSEPOINTER_TEX);
	mMousePointer.registerEvents();
	mWindow.setMouseCursorVisible(false);
}
