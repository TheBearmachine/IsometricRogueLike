#include "Tile.h"
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
	mWorldPos(worldPos)
{
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
