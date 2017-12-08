#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "EventObserver.h"

class Game;
class DrawingManager;

class GameState : public EventObserver
{
public:
	GameState(Game* owner, GameState** currentGameState) : mOwner(owner), mCurrentGameState(currentGameState) {}
	~GameState() {}

	// Event Observer
	virtual void registerEvents() = 0;
	virtual void unregisterEvents() = 0;
	virtual bool observe(const sf::Event& _event) = 0;

	virtual void update(const sf::Time &deltaTime) = 0;
	virtual void drawPrep(DrawingManager* drawingMan) = 0;

	// Transition functions
	virtual void startSimulation(size_t level) {}

	// Game State

protected:
	virtual void exit() = 0;
	virtual void entry() = 0;
	virtual void transition(GameState* from, GameState* to);

	Game* mOwner;

private:
	GameState** mCurrentGameState;
};