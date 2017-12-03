#include "Tile.h"

Tile::Tile() :
	mTextureID(-1),
	mWorldPos()
{
}

Tile::Tile(int textureID, const sf::Vector2f &worldPos) :
	mTextureID(textureID),
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

void Tile::setWorldPos(const sf::Vector2f & worldPos)
{
	mWorldPos = worldPos;
}

sf::Vector2f Tile::getWorldPos() const
{
	return mWorldPos;
}
