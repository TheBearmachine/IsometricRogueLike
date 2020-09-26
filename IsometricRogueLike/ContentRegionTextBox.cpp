#include "ContentRegionTextBox.h"
#include "DrawingManager.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>

static const std::string SCROLLER_TEX = "";
static const sf::Vector2f SCROLLER_SIZE = { 5.0f, 30.0f };
static const float SCROLLER_BORDER_THICKNESS = 1.0f;
static const float BORDER_THICKNESS = Constants::Game::ContentRegionBorderThickness;

ContentRegionTextBox::ContentRegionTextBox(const std::string & text, const sf::Vector2f & size) :
	ContentRegion(size), mTextBox(), mScroller(this, SCROLLER_SIZE, 0), mScrollerGraphics(SCROLLER_SIZE)
{
	mScroller.setParentTransform(this);
	mScroller.setPosition(getRegionUsableSize().x - BORDER_THICKNESS, BORDER_THICKNESS);
	mTextBox.setParentTransform(this);
	mTextBox.setScrollListener(this);
	mTextBox.setString(text);
	mTextBox.setPosition(BORDER_THICKNESS, BORDER_THICKNESS);
	setRegionSize(size);

	mScrollerGraphics.setOutlineThickness(-SCROLLER_BORDER_THICKNESS);
	mScrollerGraphics.setOutlineColor(Constants::Game::WindowTopBorderColor);
	mScrollerGraphics.setFillColor(Constants::Game::WindowTopFillColor);
	mScrollerGraphics.setPosition(getRegionUsableSize().x - BORDER_THICKNESS, BORDER_THICKNESS);
}

ContentRegionTextBox::~ContentRegionTextBox()
{}

void ContentRegionTextBox::drawPrep(DrawingManager * drawingMan)
{

}

void ContentRegionTextBox::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	ContentRegion::draw(target, states);

	states.transform = getGlobalTransform();
	target.draw(mTextBox, states);
	target.draw(mScrollerGraphics, states);
}

void ContentRegionTextBox::setRegionSize(const sf::Vector2f & size)
{
	ContentRegion::setRegionSize(size);
	sf::Vector2f v = getRegionUsableSize();
	v.x -= mScroller.getSize().x;
	mMouseScrollArea.setSize(size);
	mTextBox.setConfines(v);
}

void ContentRegionTextBox::setText(const std::string & text)
{
	mTextBox.setString(text);
}

void ContentRegionTextBox::onDrag(const sf::Vector2f & mouseDelta, const sf::Vector2f & mousePos, const sf::Event & button)
{
	//sf::Vector2f localMouse = -getGlobalTransform().transformPoint(-mousePos);
	//localMouse.x = mScroller.getPosition().x;
	//mScroller.setPosition(localMouse);
	//mScrollerGraphics.setPosition(localMouse);

	sf::Vector2f delta = mouseDelta;
	delta.x = 0.0f;
	mScroller.move(delta);
	mScrollerGraphics.move(delta);
	fitScroller();
	sf::Vector2f textRelativePos;

	textRelativePos.y = (mScroller.getPosition().y - BORDER_THICKNESS) /
        (getRegionUsableSize().y - mScroller.getSize().y);
	mTextBox.setTextRelativePosition(textRelativePos);
}

void ContentRegionTextBox::onScroll(const sf::Event & button)
{
	sf::Vector2f v = mTextBox.getTextPosition();
	v.y += button.mouseWheelScroll.delta * 15.0f;
	mTextBox.setTextPosition(v);
    v = mTextBox.getTextRelativePosition();
    v.x = mScroller.getPosition().x;
    v.y = v.y * (getRegionUsableSize().y - mScroller.getSize().y) + BORDER_THICKNESS;
	mScroller.setPosition(v);
	mScrollerGraphics.setPosition(v);
    fitScroller();
}

bool ContentRegionTextBox::delegateEvent(const sf::Event & _event)
{
	mTextBox.observe(_event);
	mScroller.observe(_event);
    sf::Event::EventType;

	return false;
}

void ContentRegionTextBox::resetState()
{
	mScroller.resetState();
}

void ContentRegionTextBox::fitScroller()
{
	float relLength = getRegionUsableSize().y - mScroller.getSize().y;
	if (mScroller.getPosition().y - BORDER_THICKNESS > relLength)
	{
		mScroller.setPosition(mScroller.getPosition().x, relLength + BORDER_THICKNESS);
		mScrollerGraphics.setPosition(mScroller.getPosition().x, relLength + BORDER_THICKNESS);
	}
	else if (mScroller.getPosition().y - BORDER_THICKNESS <= 0.0f)
	{
		mScroller.setPosition(mScroller.getPosition().x, BORDER_THICKNESS);
		mScrollerGraphics.setPosition(mScroller.getPosition().x, BORDER_THICKNESS);

	}

}
