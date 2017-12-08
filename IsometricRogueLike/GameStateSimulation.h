#pragma once
#include "GameState.h"
#include "Map.h"
#include "CameraController.h"
#include "Entity.h"
#include "WindowManager.h"

namespace sf
{
	class RenderWindow;
}
class Game;
class EventManager;
class GameStateMenu;

class GameStateSimulation : public GameState
{
public:
	GameStateSimulation(Game* owner, GameState** currentGameState);
	~GameStateSimulation();

	void initalize(sf::RenderWindow* window, EventManager* eventManager);

	// Event Observer
	virtual void registerEvents() override;
	virtual void unregisterEvents() override;
	virtual bool observe(const sf::Event& _event) override;

	virtual void update(const sf::Time &deltaTime) override;
	virtual void drawPrep(DrawingManager* drawingMan) override;

	// Transition functions

	// Game State
	void setGameStates(GameStateMenu* gameStateMenu);

protected:
	virtual void exit() override;
	virtual void entry() override;

private:
	Map testMap;
	Entity testEntity;
	CameraController testCamController;
	std::vector<sf::Event::EventType> mInterestedEvents;

	WindowManager mWindowManager;

	sf::RenderWindow* mWindow;
	EventManager* mEventManager;

	GameStateMenu* mGameStateMenu;
};