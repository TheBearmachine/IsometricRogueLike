#include "Dragable.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "EventManager.h"

Dragable::Dragable() :
	Dragable(nullptr, sf::FloatRect())
{
}

Dragable::Dragable(IDragListener* listener, const sf::FloatRect & area) :
	mListener(listener), mDrag(false), mInteractArea(area), previousMousePos(0.0f, 0.0f)
{
	mInterestedEvents.push_back(sf::Event::EventType::MouseMoved);
	mInterestedEvents.push_back(sf::Event::EventType::MouseButtonPressed);
	mInterestedEvents.push_back(sf::Event::EventType::MouseButtonReleased);
}

Dragable::~Dragable()
{
	unregisterEvents();
}

void Dragable::setListener(IDragListener * listener)
{
	mListener = listener;
}

void Dragable::setAction(size_t action)
{
	mAction = action;
}

void Dragable::registerEvents()
{
	if (mEventManager && !mRegistered)
	{
		mRegistered = true;
		mEventManager->registerObserver(this, mInterestedEvents);
	}
}

void Dragable::unregisterEvents()
{
	if (mEventManager && mRegistered)
	{
		mRegistered = false;
		mEventManager->unregisterObserver(this, mInterestedEvents);
	}
}

void Dragable::observe(const sf::Event & _event)
{
	sf::Vector2f mousePos;
	sf::Vector2f globPos = getGlobalTransform().transformPoint(0.0f, 0.0f);
	sf::FloatRect globRect(mInteractArea);
	globRect.left += globPos.x;
	globRect.top += globPos.y;
	switch (_event.type)
	{
	case sf::Event::MouseMoved:
		mousePos = mWindow->mapPixelToCoords(sf::Vector2i(_event.mouseMove.x, _event.mouseMove.y));
		if (mDrag)
		{
			sf::Vector2f mouseDelta = mousePos - previousMousePos;
			previousMousePos = mousePos;
			if (mListener)
				mListener->onDrag(mouseDelta, mousePos);
		}
		break;

	case sf::Event::MouseButtonPressed:
		mousePos = mWindow->mapPixelToCoords(sf::Vector2i(_event.mouseButton.x, _event.mouseButton.y));
		if (globRect.contains(mousePos))
		{
			mDrag = true;
			previousMousePos = mousePos;
		}
		break;

	case sf::Event::MouseButtonReleased:
		mDrag = false;
		break;
	}

}

void Dragable::setup(EventManager * eventManager, sf::RenderTarget * window)
{
	mEventManager = eventManager;
	mWindow = window;
}
