#include "MousePointer.h"
#include "DrawingManager.h"
#include "Item.h"
#include <SFML/Graphics/RenderWindow.hpp>

static sf::RenderWindow* mWindow;

MousePointer::MousePointer() :
    mItem(nullptr)
{
    mSprite.setParentTransform(this);
    setStaticDrawPosition(true);
    setZBuffer(1000000);
    mTooltip.setParentTransform(this);
}

MousePointer::~MousePointer()
{
}

void MousePointer::setNewTexture(const AnimationTextureSetup& animSetup)
{
    mSprite.setNewTexture(animSetup);
}

Item* MousePointer::switchItem(Item* newItem)
{
    Item* temp = mItem;
    mItem = newItem;
    return temp;
}

Item * MousePointer::getItem()
{
    return mItem;
}

Tooltip * MousePointer::getTooltip()
{
    return &mTooltip;
}

void MousePointer::update(const sf::Time & deltaTime)
{
    sf::Vector2f mousePos(sf::Mouse::getPosition(*mWindow));
    setPosition(mousePos);
    mTooltip.update(deltaTime);
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
        target.draw(*mItem, states);
    //mItem->draw(target, states);

    target.draw(mTooltip, states);
}

void MousePointer::setup(sf::RenderWindow* window)
{
    mWindow = window;
}
