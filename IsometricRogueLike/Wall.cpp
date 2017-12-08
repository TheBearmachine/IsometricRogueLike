#include "Wall.h"

Wall::Wall():
	Wall(-1, sf::Vector2f(0.0f, 0.0f))
{
}

Wall::Wall(int textureID, const sf::Vector2f & worldPos):
	mTextureID(textureID),
	mWorldPos(worldPos)
{
}

Wall::~Wall()
{
}

void Wall::setTextureID(int texID)
{
	mTextureID = texID;
}

int Wall::getTextureID() const
{
	return mTextureID;
}

void Wall::setWorldPos(const sf::Vector2f & worldPos)
{
	mWorldPos = worldPos;
}

sf::Vector2f Wall::getWorldPos() const
{
	return mWorldPos;
}
