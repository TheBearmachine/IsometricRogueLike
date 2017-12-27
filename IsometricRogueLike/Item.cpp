#include "Item.h"
#include "ResourceManager.h"
#include "DrawingManager.h"
#include <SFML/Graphics/RenderWindow.hpp>

Item::Item() :
	mItemType(Sword),
	mEqSlot(NonEquippable)
{
	setStaticDrawPosition(true);
}

Item::~Item()
{

}

void Item::setAttachment(Transformabetter * attachment)
{
	mAttachment = attachment;
}

Transformabetter * Item::getAttachment()
{
	return mAttachment;
}

void Item::setProperty(int value, int arrayIndex)
{
	mProperties[arrayIndex] = value;
}

int Item::getProperty(int arrayIndex) const
{
	return mProperties[arrayIndex];
}

void Item::setID(size_t ID)
{
	mID = ID;
}

size_t Item::getID() const
{
	return mID;
}

void Item::setItemTyp(ItemTypes type)
{
	mItemType = type;
}

Item::ItemTypes Item::getItemType() const
{
	return mItemType;
}

void Item::setEquipmentSlot(EquipmentSlot eqSlot)
{
	mEqSlot = eqSlot;
}

Item::EquipmentSlot Item::getEquipmentSlot() const
{
	return mEqSlot;
}

void Item::setItemName(const std::string & iName)
{
	mItemName = iName;
}

const std::string & Item::getItemName() const
{
	return mItemName;
}

void Item::setItemDescription(const std::string & desc)
{
	mItemDesc = desc;
}

const std::string & Item::getItemDescription() const
{
	return mItemDesc;
}

void Item::drawPrep(DrawingManager * drawingMan)
{

}

void Item::draw(sf::RenderTarget & target, sf::RenderStates states) const
{

	target.draw(mSprite, states);
}

void Item::setItemTex(const std::string & texFile)
{
	mSprite.setTexture(ResourceManager::getInstance().getTexture(texFile));
}

sf::Sprite * Item::getSprite()
{
	return &mSprite;
}
