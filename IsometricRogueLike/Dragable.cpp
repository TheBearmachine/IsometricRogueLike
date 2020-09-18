#include "Dragable.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "EventManager.h"

Dragable::Dragable() :
	Dragable(nullptr, sf::Vector2f(), 0)
{
}

Dragable::Dragable(IDragListener* listener, const sf::Vector2f & size, size_t action) :
	Clickable(size), mListener(listener)
{

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

void Dragable::onDragInside(const sf::Vector2f & mouseDelta, const sf::Vector2f & mousePos, const sf::Event& button)
{
	if (mListener)
		mListener->onDrag(mouseDelta, mousePos, button);
}
