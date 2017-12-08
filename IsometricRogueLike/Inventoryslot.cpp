#include "Inventoryslot.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "DrawingManager.h"
#include "Constants.h"
#include "ResourceManager.h"

static const std::string TEXTURE_FILE = Constants::Filepaths::ImagesFolder + "Inventoryslot.png";

Inventoryslot::Inventoryslot() :
	Inventoryslot(0U)
{
}

Inventoryslot::Inventoryslot(size_t ID) :
	mSprite(ResourceManager::getInstance().getTexture(TEXTURE_FILE))
{
}

Inventoryslot::~Inventoryslot()
{
}

void Inventoryslot::setListener(IInventoryslotListener * listener)
{
}

void Inventoryslot::setID(size_t ID)
{
}

sf::Vector2f Inventoryslot::getSize() const
{
	return sf::Vector2f((float)mSprite.getTextureRect().width, (float)mSprite.getTextureRect().height);
}

bool Inventoryslot::observe(const sf::Event & _event)
{
	return false;
}

void Inventoryslot::onMouseOver(bool mouseOver)
{
}

void Inventoryslot::onClickInside()
{
}

void Inventoryslot::onReleaseInside()
{
}

void Inventoryslot::onDragInside(const sf::Vector2f & mouseDelta, const sf::Vector2f & mousePos)
{
}

void Inventoryslot::drawPrep(DrawingManager * drawingMan)
{
	drawingMan->addDrawable(this);
}

void Inventoryslot::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform = getGlobalTransform();
	target.draw(mSprite, states);
}
