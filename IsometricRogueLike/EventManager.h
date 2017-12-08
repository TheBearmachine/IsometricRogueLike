#pragma once

#include <unordered_map>
#include <vector>
#include <SFML/Window/Event.hpp>

class EventObserver;
namespace sf
{
	class RenderTarget;
}

class EventManager
{
public:
	EventManager();
	~EventManager();

	void registerObserver(EventObserver* observer, const std::vector<sf::Event::EventType>& types);
	void registerObserver(EventObserver* observer, const sf::Event::EventType& type);
	void unregisterObserver(EventObserver* observer, const std::vector<sf::Event::EventType>& types);
	void unregisterObserver(EventObserver* observer, const sf::Event::EventType& type);
	void notify(const sf::Event& _event, sf::RenderTarget* target) const;

private:
	typedef std::vector<EventObserver*> ObserverVec;
	std::unordered_map<sf::Event::EventType, ObserverVec> mObservers;
};
