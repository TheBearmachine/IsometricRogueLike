#include "Tile.h"
#include "Item.h"
#include "Constants.h"
#include <cmath>

Tile::Tile() :
	mTextureID(-1),
	mWallTextureID(-1)
{
}

Tile::Tile(int textureID, const sf::Vector2f &worldPos) :
	mTextureID(textureID),
	mWallTextureID(textureID),
	mWorldPos(worldPos),
	mFadeCurrent(0.0f), mFadeMax(1.0f),
	mOccupant(nullptr)
{
	setWorldPos(worldPos);
}

Tile::~Tile()
{

}

void Tile::setTextureID(int texID)
{
	mTextureID = texID;
}

int Tile::getTextureID() const
{
	return mTextureID;
}

void Tile::setWallTextureID(int texID)
{
	mWallTextureID = texID;
}

int Tile::getWallTextureID() const
{
	return mWallTextureID;
}

void Tile::setWorldPos(const sf::Vector2f & worldPos)
{
	mWorldPos = worldPos;
	setPosition(sf::Vector2f(worldPos.x + Constants::World::Tile::HalfWidth, worldPos.y));
}

sf::Vector2f Tile::getWorldPos() const
{
	return mWorldPos;
}

void Tile::setArrayIndex(const sf::Vector2i & arrayIndex)
{
	mArrayIndex = arrayIndex;
}

sf::Vector2i Tile::getArrayIndex() const
{
	return mArrayIndex;
}

void Tile::setFadeMax(float val)
{
	mFadeMax = mFadeCurrent = val;
}

void Tile::reduceFadeCurrent(float deltaVal)
{
	mFadeCurrent = std::fmaxf(0.0f, mFadeCurrent - deltaVal);
}

float Tile::getFadeRatio() const
{
	return mFadeCurrent / mFadeMax;
}

void Tile::setOccupant(Entity * occupant)
{
	mOccupant = occupant;
}

const Entity * Tile::getOccupant() const
{
	return mOccupant;
}

void Tile::addItem(Item * item)
{
	mItems.push_back(item);
	item->setParentTransform(this);
	sf::Vector2f origin(Constants::Items::HalfWidth, -Constants::Items::HalfHeight);
	sf::Vector2f scale(Constants::Items::WidthRatio, Constants::Items::HeightRatio);
	item->getSprite()->setScale(scale);
	item->getSprite()->setOrigin(origin);
}

void Tile::removeItem(Item * item)
{
	item->getSprite()->setScale(1.0f, 1.0f);
	item->getSprite()->setOrigin(0.0f, 0.0f);

	size_t pos = 0;
	// Find location of item in vector
	for (size_t i = 0; i < mItems.size(); i++)
	{
		if (mItems[i] == item)
		{
			pos = i;
			break;
		}
	}

	// Bubble it up to the top and remove it
	for (size_t i = pos; i < mItems.size() - 1; i++)
	{
		Item* temp = mItems[i];
		mItems[i] = mItems[i + 1];
		mItems[i + 1] = temp;
	}
	mItems.pop_back();
}

std::vector<Item*> Tile::getItems()
{
	return mItems;
}

Item** Tile::getItem(size_t ID)
{
	return &mItems[ID];
}

size_t Tile::getNrItems() const
{
	return mItems.size();
}

void Tile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform = getGlobalTransform();

	for (auto i : mItems)
	{
		sf::Vector2f origin(Constants::Items::HalfWidth, -Constants::Items::HalfHeight);
		sf::Vector2f scale(Constants::Items::WidthRatio, Constants::Items::HeightRatio);
		i->getSprite()->setScale(scale);
		i->getSprite()->setOrigin(origin);
		i->draw(target, states);
		i->getSprite()->setScale(1.0f, 1.0f);
		i->getSprite()->setOrigin(0.0f, 0.0f);
	}
}
