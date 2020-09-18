#include "Clickable.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

static sf::RenderTarget* mWindow;

Clickable::Clickable() :
	Clickable(sf::Vector2f(0.0f, 0.0f))
{

}

Clickable::Clickable(const sf::Vector2f &size) :
	mSize(size), mMouseInside(false), mDrag(false)
{
	mInterestedEvents.push_back(sf::Event::EventType::MouseMoved);
	mInterestedEvents.push_back(sf::Event::EventType::MouseButtonPressed);
	mInterestedEvents.push_back(sf::Event::EventType::MouseButtonReleased);
}

Clickable::~Clickable()
{
	unregisterEvents();
}

void Clickable::setSize(const sf::Vector2f & size)
{
	mSize = size;
}

void Clickable::unregisterEvents()
{
	EventObserver::unregisterEvents();
	mDrag = false;
}

bool Clickable::observe(const sf::Event & _event)
{
	bool retVal = false;
	sf::Vector2f mousePos;
	sf::Vector2f globPos = getGlobalTransform().transformPoint(0.0f, 0.0f);
	sf::FloatRect globRect(globPos, mSize);
	switch (_event.type)
	{
	case sf::Event::MouseMoved:
		mousePos = mWindow->mapPixelToCoords(sf::Vector2i(_event.mouseMove.x, _event.mouseMove.y));
		if (mDrag)
		{
			sf::Vector2f mouseDelta = mousePos - mPreviousMousePos;
			mPreviousMousePos = mousePos;
			onDragInside(mouseDelta, mousePos, _event); // Move this logic to dragable?
		}

		if (globRect.contains(mousePos))
		{
			retVal = true;
			if (!mMouseInside)
			{
				mMouseInside = true;

				onMouseOver(true);
			}
		}
		else
		{
			if (mMouseInside)
			{
				mMouseInside = false;
				//mDrag = false;
				onMouseOver(false);
			}
		}
		break;

	case sf::Event::MouseButtonPressed:
		mousePos = mWindow->mapPixelToCoords(sf::Vector2i(_event.mouseButton.x, _event.mouseButton.y));
		if (mMouseInside)
		{
			onClickInside(_event);
			mPreviousMousePos = mousePos;
			mDrag = true;

			retVal = true;
		}
		break;

	case sf::Event::MouseButtonReleased:

		if (mMouseInside && mDrag)
		{
			onReleaseInside(_event);
			retVal = true;
		}
		mDrag = false;
		break;
	}
	return retVal;
}

void Clickable::onMouseOver(bool mouseOver)
{

}

void Clickable::onClickInside(const sf::Event& button)
{

}

void Clickable::onReleaseInside(const sf::Event& button)
{

}

void Clickable::onDragInside(const sf::Vector2f & mouseDelta, const sf::Vector2f & mousePos, const sf::Event& button)
{

}

void Clickable::resetState()
{
	mMouseInside = false;
	mDrag = false;
}

void Clickable::setup(sf::RenderTarget * window)
{
	mWindow = window;
}
