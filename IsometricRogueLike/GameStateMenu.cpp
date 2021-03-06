#include "GameStateMenu.h"
#include "GameStateSimulation.h"
#include "ContentRegionInventory.h"
#include "Constants.h"
#include <SFML/Graphics/RenderWindow.hpp>

static const std::string GUI_BUTTON = Constants::Filepaths::ImagesFolder + "GUIButton.png";
static const std::string FONT = Constants::Filepaths::DefaultFont;

GameStateMenu::GameStateMenu(Game* owner, GameState** currentGameState) :
	GameState(owner, currentGameState), mMainMenu(sf::Vector2f(250.0f, 300.0f))
{

}

GameStateMenu::~GameStateMenu()
{

}

void GameStateMenu::initalize(sf::RenderWindow * window, EventManager * eventManager)
{
	mWindow = window;
	mEventManager = eventManager;

	sf::Vector2f menuPos;
	menuPos.x = ((float)window->getSize().x - mMainMenu.getBackgroundSize().x) / 2.0f;
	menuPos.y = ((float)window->getSize().y - mMainMenu.getBackgroundSize().y) / 2.0f;
	mMainMenu.setPosition(menuPos);

	sf::Vector2f buttonPos;
	Button* button = new Button(this, GUI_BUTTON, 0);
	buttonPos.x = (mMainMenu.getBackgroundSize().x - button->getSize().x) / 2.0f;
	//buttonPos.y = (mMainMenu.getBackgroundSize().y - button->getSize().y) / 2.0f;
	buttonPos.y = 20.0f;
	button->setPosition(buttonPos);
	button->setTextSize(15);
	button->setTextString("Play");
	//button->setTooltipText("Start a new game? Just click it, not like you have a choise of buttons.");
	//button->setActive(false);
	mMainMenu.addButton(button);
	mMainMenu.registerEvents();


	// Test window
	/*Window* testWindow = new Window("Test Window", sf::Vector2f(100.0f, 50.0f), sf::Vector2f());
	ContentRegionInventory* cr = new ContentRegionInventory(12, 5);
	mWindowManager.addWindow(testWindow);
	testWindow->setWindowContentSize(cr->getRegionSize());
	testWindow->addContentRegion(cr);
	testWindow->registerEvents();*/

}

void GameStateMenu::registerEvents()
{
	mMainMenu.registerEvents();
	mWindowManager.registerEvents();
}

void GameStateMenu::unregisterEvents()
{
	mMainMenu.unregisterEvents();
	mWindowManager.unregisterEvents();
}

bool GameStateMenu::observe(const sf::Event & _event)
{
	return false;
}

void GameStateMenu::exit()
{
	unregisterEvents();
}

void GameStateMenu::entry()
{
	registerEvents();
}

void GameStateMenu::update(const sf::Time & deltaTime)
{
	mWindowManager.clearGarbage();
}

void GameStateMenu::drawPrep(DrawingManager* drawingMan)
{
	mMainMenu.drawPrep(drawingMan);
	mWindowManager.drawPrep(drawingMan);
}

void GameStateMenu::buttonAction(unsigned int action)
{
	switch (action)
	{
	case MainMenuButtonActions::StartGame:
		startSimulation(0);
		break;

	default:
		break;
	}
}

void GameStateMenu::startSimulation(size_t level)
{
	transition(this, mGameStateSimulation);
}

void GameStateMenu::setGameStates(GameStateSimulation * gameStateSimulation)
{
	mGameStateSimulation = gameStateSimulation;
}
