#include "Inventoryslot.h"
#include <SFML/Graphics/RenderTarget.hpp>
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

void Inventoryslot::observe(const sf::Event & _event)
{
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

void Inventoryslot::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}
