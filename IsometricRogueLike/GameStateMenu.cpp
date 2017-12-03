#include "GameStateMenu.h"
#include "ContentRegionInventory.h"
#include <SFML/Graphics/RenderWindow.hpp>

GameStateMenu::GameStateMenu(Game* owner, GameState* currentGameState) :
	GameState(owner, currentGameState),
	testWindow("Test Window", sf::Vector2f(100.0f, 50.0f), sf::Vector2f(330.0f, 200.0f))
{
	//testWindow.setPosition(100, 20);
}

GameStateMenu::~GameStateMenu()
{

}

void GameStateMenu::initalize(sf::RenderWindow * window, EventManager * eventManager)
{
	mWindow = window;
	mEventManager = eventManager;
	testWindow.setup(mEventManager, mWindow);

	//sf::Vector2f halfSize = testWindow.getContentSize();
	//halfSize.y = halfSize.y / 2.0f - 3.0f;
	ContentRegion* cr = new ContentRegionInventory(12, 5);
	testWindow.setWindowContentSize(cr->getRegionSize());
	testWindow.addContentRegion(cr);
	//cr = new ContentRegion(halfSize);
	//cr->move(0.0f, halfSize.y + 6.0f);
	//testWindow.addContentRegion(cr);
	testWindow.registerEvents();

}

void GameStateMenu::registerEvents()
{

}

void GameStateMenu::unregisterEvents()
{

}

void GameStateMenu::observe(const sf::Event & _event)
{

}

void GameStateMenu::exit()
{

}

void GameStateMenu::entry()
{

}

void GameStateMenu::update(const sf::Time & deltaTime)
{

}

void GameStateMenu::draw(sf::RenderTarget * window)
{
	window->draw(testWindow);
}
