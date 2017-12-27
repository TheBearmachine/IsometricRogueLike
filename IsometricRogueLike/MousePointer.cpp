#include "MousePointer.h"
#include "DrawingManager.h"
#include "Item.h"
#include <SFML/Graphics/RenderTarget.hpp>

static sf::RenderTarget* mWindow;

MousePointer::MousePointer() :
	mItem(nullptr)
{
	mInterestedEvents.push_back(sf::Event::EventType::MouseMoved);
	mInterestedEvents.push_back(sf::Event::EventType::MouseButtonPressed);
	mInterestedEvents.push_back(sf::Event::EventType::MouseButtonReleased);
	mSprite.setParentTransform(this);
	setStaticDrawPosition(true);
	setZBuffer(1000000);
}

MousePointer::~MousePointer()
{
}

void MousePointer::setSprite(const std::string & textureName)
{
	mSprite.setSpriteTexture(textureName);
}

Item* MousePointer::switchItem(Item* newItem)
{
	Item* temp = mItem;
	mItem = newItem;
	if (newItem)
		newItem->setAttachment(this);
	return temp;
}

Item * MousePointer::getItem()
{
	return mItem;
}

bool MousePointer::observe(const sf::Event & _event)
{
	sf::Vector2f mousePos;
	switch (_event.type)
	{
	case sf::Event::EventType::MouseMoved:
		mousePos = mWindow->mapPixelToCoords(sf::Vector2i(_event.mouseMove.x, _event.mouseMove.y));
		setPosition(mousePos);
		break;

	case sf::Event::EventType::MouseButtonPressed:

		break;


	case sf::Event::EventType::MouseButtonReleased:

		break;

	default:
		break;
	}

	return false;
}

void MousePointer::drawPrep(DrawingManager * drawingMan)
{
	drawingMan->addDrawable(this);
}

void MousePointer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform = getGlobalTransform();

	target.draw(mSprite, states);

	if (mItem)
		mItem->draw(target, states);
}

void MousePointer::setup(sf::RenderTarget * window)
{
	mWindow = window;
}
