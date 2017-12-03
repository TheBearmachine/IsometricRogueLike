#pragma once

namespace sf
{
	class Event;
}

class EventObserver
{
public:
	EventObserver() : mRegistered(false) {}
	virtual ~EventObserver() {}

	virtual void observe(const sf::Event& _event) = 0;
	virtual void registerEvents() = 0;
	virtual void unregisterEvents() = 0;

protected:
	bool mRegistered;
};