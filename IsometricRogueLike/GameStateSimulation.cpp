#include "GameStateSimulation.h"
#include "Constants.h"
#include "ContentRegionInventory.h"
#include "Creature.h"
#include "Object.h"
#include "EventManager.h"
#include "VectorFunctions.h"
#include "IsometricConversion.h"
#include "ContentRegionCharacterAttributes.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

static const std::string PLAYER_TEXTURE = Constants::Filepaths::ImagesFolder + "Monk.png";
static const std::string CHEST_TEXTURE = Constants::Filepaths::ImagesFolder + "WoodenChest.png";

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
	GameState(owner, currentGameState)
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
	Entity::setup(&mEntityManager);
	mMapManager.setupMap(TEST_LEVEL, 10, 10);
	sf::FloatRect screenSize(sf::Vector2f(0.0f, 0.0f), window->getView().getSize());
	Creature* testEntity = new Creature(PLAYER_TEXTURE);
	testEntity->moveToTile(sf::Vector2i(2, 2), mMapManager.getCurrentMap());

	Object* obj = new Object(CHEST_TEXTURE, sf::Vector2i(6, 2), mMapManager.getCurrentMap());

	testCamController.initalize(screenSize, window);
	testSimController.initalize(mMapManager.getCurrentMap(), testEntity);
	mEntityManager.addEntity(testEntity);
	mEntityManager.addEntity(obj);
	mEntityManager.setLightgiver(testEntity);
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
			Window* testWindow = new Window("Inventory", sf::Vector2f(100.0f, 50.0f), sf::Vector2f());
			ContentRegionInventory* cr = new ContentRegionInventory(12, 5);
			mWindowManager.addWindow(testWindow);
			testWindow->setWindowContentSize(cr->getRegionSize());
			testWindow->addContentRegion(cr);
			testWindow->registerEvents();
		}
		else if (_event.key.code == sf::Keyboard::C)
		{
			// Test window
			Window* testWindow = new Window("Character", sf::Vector2f(100.0f, 50.0f), sf::Vector2f());
			ContentRegionCharacterAttributes* cr = new ContentRegionCharacterAttributes();
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
		testCamController.updateCamera();
	}

	mEntityManager.update(deltaTime);
	mMapManager.update(deltaTime);
	mWindowManager.clearGarbage();
}

void GameStateSimulation::drawPrep(DrawingManager* drawingMan)
{
	mMapManager.drawPrep(drawingMan);
	mEntityManager.drawPrep(drawingMan);
	mWindowManager.drawPrep(drawingMan);
}
