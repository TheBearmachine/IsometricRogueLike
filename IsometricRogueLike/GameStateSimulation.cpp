#include "GameStateSimulation.h"
#include "Constants.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "ContentRegionInventory.h"
#include "EventManager.h"
#include "VectorFunctions.h"
#include "IsometricConversion.h"

static const std::string PLAYER_TEXTURE = Constants::Filepaths::ImagesFolder + "Monk.png";

static const int TEST_LEVEL[]{
	-1,-1,-1,-1,-1,-1,-1, 1, 1, 1,
	-1,-1,-1,-1,-1,-1,-1, 1, 1, 1,
	-1,-1, 0, 0, 0, 0, 0, 1, 1, 1,
	-1,-1, 0, 0, 0, 0, 0, 1, 1, 1,
	-1,-1, 0, 0, 0,-1,-1, 1, 1, 1,
	-1,-1, 0, 0, 0,-1,-1, 1, 1, 1,
	-1,-1, 0, 0, 0,-1,-1, 1, 1, 1,
	-1,-1, 0, 0, 0,-1,-1, 1, 1, 1,
	-1,-1, 0, 0, 0,-1,-1,-1,-1,-1,
	-1,-1, 0, 0, 0,-1,-1,-1,-1,-1
};

GameStateSimulation::GameStateSimulation(Game* owner, GameState** currentGameState) :
	GameState(owner, currentGameState), testEntity(PLAYER_TEXTURE)
{
	mInterestedEvents.push_back(sf::Event::KeyPressed);
}

GameStateSimulation::~GameStateSimulation()
{

}

void GameStateSimulation::initalize(sf::RenderWindow * window, EventManager* eventManager)
{
	mWindow = window;
	mEventManager = eventManager;
	mMapManager.setupMap(TEST_LEVEL, 10, 10);
	sf::FloatRect screenSize(sf::Vector2f(0.0f, 0.0f), window->getView().getSize());
	testEntity.setPosition(IsometricConversion::toIsometric(
		sf::Vector2f(Constants::World::Tile::Width * 2.0f, Constants::World::Tile::Width * 2.0f)));
	testCamController.initalize(screenSize, window);
	testSimController.setCurrentMap(mMapManager.getCurrentMap());
	testSimController.setControllableEntity(&testEntity);
}

void GameStateSimulation::registerEvents()
{
	mEventManager->registerObserver(this, mInterestedEvents);
	testSimController.registerEvents();
	mWindowManager.registerEvents();
}

void GameStateSimulation::unregisterEvents()
{
	mEventManager->unregisterObserver(this, mInterestedEvents);
	testSimController.unregisterEvents();
	mWindowManager.unregisterEvents();
}

bool GameStateSimulation::observe(const sf::Event & _event)
{
	switch (_event.type)
	{
	case sf::Event::KeyPressed:
		if (_event.key.code == sf::Keyboard::I)
		{
			// Test window
			Window* testWindow = new Window("Test Window", sf::Vector2f(100.0f, 50.0f), sf::Vector2f());
			ContentRegionInventory* cr = new ContentRegionInventory(12, 5);
			mWindowManager.addWindow(testWindow);
			testWindow->setWindowContentSize(cr->getRegionSize());
			testWindow->addContentRegion(cr);
			testWindow->registerEvents();
		}
		else if (_event.key.code == sf::Keyboard::Escape)
		{
			mWindow->close();
		}
		break;

	default:
		break;
	}

	return false;
}

void GameStateSimulation::setGameStates(GameStateMenu * gameStateMenu)
{
	mGameStateMenu = gameStateMenu;
}

void GameStateSimulation::exit()
{
	unregisterEvents();
}

void GameStateSimulation::entry()
{
	registerEvents();
}

void GameStateSimulation::update(const sf::Time & deltaTime)
{
	sf::Vector2f offset;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		offset.x = -1.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		offset.x = 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		offset.y = -1.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		offset.y = 1.0f;
	}
	if (offset != sf::Vector2f(0.0f, 0.0f))
	{
		VectorFunctions::normalizeVector(offset);
		offset *= deltaTime.asSeconds() * Constants::Camera::Speed;

		testCamController.moveCamera(offset);
		//testEntity.move(offset);
		testCamController.updateCamera();
	}

	testEntity.update(deltaTime);
	mWindowManager.clearGarbage();
}

void GameStateSimulation::drawPrep(DrawingManager* drawingMan)
{
	mMapManager.drawPrep(drawingMan);
	testEntity.drawPrep(drawingMan);
	mWindowManager.drawPrep(drawingMan);
}
