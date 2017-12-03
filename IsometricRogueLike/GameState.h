#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "EventObserver.h"

class Game;

class GameState : public EventObserver
{
public:
	GameState(Game* owner, GameState* currentGameState) : mOwner(owner), mCurrentGameState(currentGameState) {}
	~GameState() {}

	// Event Observer
	virtual void registerEvents() = 0;
	virtual void unregisterEvents() = 0;
	virtual void observe(const sf::Event& _event) = 0;

	virtual void update(const sf::Time &deltaTime) = 0;
	virtual void draw(sf::RenderTarget* window) = 0;

	// Transition functions


	// Game State
protected:
	virtual void exit() = 0;
	virtual void entry() = 0;
	virtual void transition(GameState* from, GameState* to);

	Game* mOwner;

private:
	GameState* mCurrentGameState;
};