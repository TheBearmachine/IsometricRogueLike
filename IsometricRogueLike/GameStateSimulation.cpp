#include "GameStateSimulation.h"
#include "Constants.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "EventManager.h"
#include "VectorFunctions.h"

static const char* TEXTURE_SHIZZLE = "Resources/Images/FloorTiles.png";

static const int TEST_LEVEL[]{
	-0,-1,-1,-1,-1,-1,-1,-1,-1,-0,
	-0,-1,-1,-1,-1,-1,-1,-1,-1,-0,
	-0,-1, 1, 1, 2, 2, 1, 1,-1,-0,
	-0,-1, 1, 1, 2, 2, 1, 1,-1,-0,
	-0,-1, 2, 2, 2, 2, 2, 2,-1,-0,
	-0,-1, 2, 2, 2, 2, 2, 2,-1,-0,
	-0,-1, 1, 1, 2, 2, 1, 1,-1,-0,
	-0,-1, 1, 1, 2, 2, 1, 1,-1,-0,
	-0,-1,-1,-1,-1,-1,-1,-1,-1,-0,
	-0,-1,-1,-1,-1,-1,-1,-1,-1,-0
};

GameStateSimulation::GameStateSimulation(Game* owner, GameState* currentGameState) :
	GameState(owner, currentGameState)
{

}

GameStateSimulation::~GameStateSimulation()
{

}

void GameStateSimulation::initalize(sf::RenderWindow * window, EventManager* eventManager)
{
	mWindow = window;
	mEventManager = eventManager;
	testMap.setupMap(TEXTURE_SHIZZLE, TEST_LEVEL, 10, 10);
	testMap.updateVertexArray(sf::Vector2f(0.0f, 0.0f));
	sf::FloatRect screenSize(sf::Vector2f(0.0f, 0.0f), window->getView().getSize());
	testCamController.initalize(screenSize, window);
	testCamController.positionCamera(sf::Vector2f(0.0f, 0.0f));
}

void GameStateSimulation::registerEvents()
{

}

void GameStateSimulation::unregisterEvents()
{

}

void GameStateSimulation::observe(const sf::Event & _event)
{

}

void GameStateSimulation::exit()
{

}

void GameStateSimulation::entry()
{

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
}

void GameStateSimulation::draw(sf::RenderTarget * window)
{
	window->draw(testMap);
}
