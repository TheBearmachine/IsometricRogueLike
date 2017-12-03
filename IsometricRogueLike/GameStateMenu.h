#pragma once
#include "GameState.h"
#include "Window.h"


namespace sf
{
	class RenderWindow;
}
class Game;
class EventManager;

class GameStateMenu : public GameState
{
public:
	GameStateMenu(Game* owner, GameState* currentGameState);
	~GameStateMenu();

	void initalize(sf::RenderWindow* window, EventManager* eventManager);

	// Event Observer
	virtual void registerEvents() override;
	virtual void unregisterEvents() override;
	virtual void observe(const sf::Event& _event) override;

	virtual void update(const sf::Time &deltaTime) override;
	virtual void draw(sf::RenderTarget* window) override;

	// Transition functions

	// Game State
protected:
	virtual void exit();
	virtual void entry();

private:
	Window testWindow;
	sf::RenderWindow* mWindow;
	EventManager* mEventManager;
};