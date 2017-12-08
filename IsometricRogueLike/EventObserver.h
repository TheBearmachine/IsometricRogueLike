#pragma once

namespace sf
{
	class Event;
}

class EventObserver
{
public:
	EventObserver() : mRegistered(false), mStaticPosition(true) {}
	virtual ~EventObserver() {}

	void setStaticEventPosition(bool staticPosition) { mStaticPosition = staticPosition; }
	bool getStaticEventPosition() const { return mStaticPosition; }

	virtual bool observe(const sf::Event& _event) = 0;
	virtual void registerEvents() = 0;
	virtual void unregisterEvents() = 0;

protected:
	bool mRegistered;

private:
	bool mStaticPosition;
};