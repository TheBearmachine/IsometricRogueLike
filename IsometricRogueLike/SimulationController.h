#pragma once
#include "EventObserver.h"
#include "Movement.h"
#include <SFML/Window/Event.hpp>
#include <vector>

class Map;
class Creature;
class EventManager;
namespace sf
{
	class RenderTarget;
}

class SimulationController : public EventObserver, public IMovementListener
{
public:
	SimulationController();
	~SimulationController();

	void initalize(Map* map, Creature* controllableEntity);

	virtual bool observe(const sf::Event& _event) override;
	virtual void registerEvents() override;
	virtual void unregisterEvents() override;

	void onReachTile(const sf::Vector2f &clientPos) override;

	static void setup(sf::RenderTarget* target, EventManager* eventManager);

private:
	std::vector<sf::Event::EventType> mInterestedEvents;
	Map* mCurrentMap;
	Creature* mControllableEntity;
};