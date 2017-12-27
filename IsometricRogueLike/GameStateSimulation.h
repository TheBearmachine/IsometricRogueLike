#pragma once
#include "GameState.h"
#include "Map.h"
#include "CameraController.h"
#include "SimulationController.h"
#include "MapManager.h"
#include "EntityManager.h"
#include "WindowManager.h"
#include "ItemManager.h"

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
	CameraController testCamController;
	SimulationController testSimController;
	std::vector<sf::Event::EventType> mInterestedEvents;

	WindowManager mWindowManager;
	MapManager mMapManager;
	EntityManager mEntityManager;
	ItemManager mItemManager;

	sf::RenderWindow* mWindow;
	EventManager* mEventManager;

	GameStateMenu* mGameStateMenu;
};