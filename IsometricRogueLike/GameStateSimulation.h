#pragma once
#include "GameState.h"
#include "Map.h"
#include "CameraController.h"

namespace sf
{
	class RenderWindow;
}
class Game;
class EventManager;

class GameStateSimulation : public GameState
{
public:
	GameStateSimulation(Game* owner, GameState* currentGameState);
	~GameStateSimulation();

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
	virtual void exit() override;
	virtual void entry() override;

private:
	Map testMap;
	CameraController testCamController;
	sf::RenderWindow* mWindow;
	EventManager* mEventManager;
};