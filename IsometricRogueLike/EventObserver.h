#pragma once
#include <SFML/Window/Event.hpp>
#include <vector>

class EventManager;

class EventObserver
{
public:
	EventObserver() : mRegistered(false), mStaticPosition(true) {}
	virtual ~EventObserver() {}

	void setStaticEventPosition(bool staticPosition) { mStaticPosition = staticPosition; }
	bool getStaticEventPosition() const { return mStaticPosition; }

	virtual bool observe(const sf::Event& _event) = 0;
	virtual void registerEvents();
	virtual void unregisterEvents();

	static void setup(EventManager* eventManager);

protected:
	bool mRegistered;
	std::vector<sf::Event::EventType> mInterestedEvents;

private:
	bool mStaticPosition;
};