#include "ContentRegion.h"
#include "DrawingManager.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>

static const float BORDER_THICKNESS = Constants::Game::ContentRegionBorderThickness;

ContentRegion::ContentRegion() :
	ContentRegion(sf::Vector2f())
{

}

ContentRegion::ContentRegion(const sf::Vector2f & size) :
	mRegionBG(size)
{
	mRegionBG.setFillColor(sf::Color(200, 200, 200, 100));
	mRegionBG.setOutlineThickness(-BORDER_THICKNESS);
	mRegionBG.setOutlineColor(sf::Color(230, 230, 230, 200));
}

ContentRegion::~ContentRegion()
{

}

bool ContentRegion::delegateEvent(const sf::Event & _event)
{
	return false;
}

void ContentRegion::setRegionSize(const sf::Vector2f & size)
{
	mRegionBG.setSize(size);
}

sf::Vector2f ContentRegion::getRegionSize() const
{
	return mRegionBG.getSize();
}

sf::Vector2f ContentRegion::getRegionUsableSize() const
{
	sf::Vector2f retSize = mRegionBG.getSize();
	retSize.x -= 2.0f *BORDER_THICKNESS;
	retSize.y -= 2.0f *BORDER_THICKNESS;
	return retSize;
}

void ContentRegion::drawPrep(DrawingManager * drawingMan)
{
	drawingMan->addDrawable(this);
}

void ContentRegion::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform = getGlobalTransform();
	target.draw(mRegionBG, states);
}

void ContentRegion::resetState()
{}
