#pragma once
#include "GameState.h"
#include "WindowManager.h"
#include "Menu.h"
#include "EnhancedText.h"

namespace sf
{
	class RenderWindow;
}
class Game;
class EventManager;
class GameStateSimulation;

class GameStateMenu : public GameState, public IButtonListener
{
public:
	GameStateMenu(Game* owner, GameState** currentGameState);
	~GameStateMenu();

	void initalize(sf::RenderWindow* window, EventManager* eventManager);

	// Event Observer
	virtual void registerEvents() override;
	virtual void unregisterEvents() override;
	virtual bool observe(const sf::Event& _event) override;

	virtual void update(const sf::Time &deltaTime) override;
	virtual void drawPrep(DrawingManager* drawingMan) override;

	void buttonAction(unsigned int action) override;

	// Transition functions
	virtual void startSimulation(size_t level) override;

	// Game State
	void setGameStates(GameStateSimulation* gameStateSimulation);

protected:
	virtual void exit();
	virtual void entry();

private:
	enum MainMenuButtonActions
	{
		StartGame
	};

	WindowManager mWindowManager;
	sf::RenderWindow* mWindow;
	EventManager* mEventManager;

	Menu mMainMenu;

	GameStateSimulation* mGameStateSimulation;
};