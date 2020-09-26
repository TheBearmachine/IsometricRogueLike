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
	mWindow(sf::VideoMode(1600, 900), APP_TITLE),
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

		mMousePointer.update(dt);
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
		if (currEvent.type == sf::Event::EventType::Resized)
		{
			mWindow.create(sf::VideoMode(currEvent.size.width, currEvent.size.height), APP_TITLE);
			mWindow.setMouseCursorVisible(false);
		}
		mEventManager.notify(currEvent, &mWindow);
	}
}

void Game::initialize()
{
	Tooltip* ttp = mMousePointer.getTooltip();

	Clickable::setup(&mWindow);
	EventObserver::setup(&mEventManager);
	MousePointer::setup(&mWindow);
	Button::setTooltipPointer(ttp);
	Window::setup(&mWindow);
	Window::setTooltipPointer(ttp);
	WindowManager::setup(&mEventManager);
	ItemManager::setMousePointer(&mMousePointer);
	Inventoryslot::setTooltipPointer(ttp);
	SimulationController::setup(&mWindow, &mEventManager, &mMousePointer);
	ItemDatabase::getInstance();

	mGameStateSimulation.initalize(&mWindow, &mEventManager);
	mGameStateMenu.initalize(&mWindow, &mEventManager);

	mGameStateMenu.setGameStates(&mGameStateSimulation);
	mGameStateSimulation.setGameStates(&mGameStateMenu);

	mCurrentState = &mGameStateMenu;

	AnimationTextureSetup ats(MOUSEPOINTER_TEX, 2, 1, 2, 0.3f);
	mMousePointer.setNewTexture(ats);
	mWindow.setMouseCursorVisible(false);
}
