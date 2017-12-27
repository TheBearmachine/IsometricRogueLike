#include "EventObserver.h"
#include "EventManager.h"

static EventManager* mEventManager;

void EventObserver::registerEvents()
{
	if (mEventManager && !mRegistered)
	{
		mRegistered = true;
		mEventManager->registerObserver(this, mInterestedEvents);
	}
}

void EventObserver::unregisterEvents()
{
	if (mEventManager && mRegistered)
	{
		mRegistered = false;
		mEventManager->unregisterObserver(this, mInterestedEvents);
	}
}

void EventObserver::setup(EventManager * eventManager)
{
	mEventManager = eventManager;
}
