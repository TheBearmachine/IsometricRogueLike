#include "Tile.h"
#include "Constants.h"
#include <cmath>

Tile::Tile() :
	mTextureID(-1),
	mWallTextureID(-1),
	mWorldPos()
{
}

Tile::Tile(int textureID, const sf::Vector2f &worldPos) :
	mTextureID(textureID),
	mWallTextureID(textureID),
	mWorldPos(worldPos),
	mWorldPosCenter(worldPos),
	mFadeCurrent(0.0f), mFadeMax(1.0f),
	mOccupant(nullptr)
{
	mWorldPosCenter.x += Constants::World::Tile::HalfWidth;
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
	mWorldPosCenter = mWorldPos = worldPos;
	mWorldPosCenter.x += Constants::World::Tile::HalfWidth;
}

sf::Vector2f Tile::getWorldPos() const
{
	return mWorldPos;
}

sf::Vector2f Tile::getWorldPosCenter() const
{
	return mWorldPosCenter;
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
