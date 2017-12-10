#pragma once
#include "EventObserver.h"
#include <SFML/Window/Event.hpp>
#include <vector>

class Map;
class EventManager;
namespace sf
{
	class RenderTarget;
}

class SimulationController: public EventObserver
{
public:
	SimulationController();
	~SimulationController();

	void setCurrentMap(Map* map);

	virtual bool observe(const sf::Event& _event) override;
	virtual void registerEvents() override;
	virtual void unregisterEvents() override;

	static void setup(sf::RenderTarget* target, EventManager* eventManager);

private:
	std::vector<sf::Event::EventType> mInterestedEvents;
	Map* mCurrentMap;
};